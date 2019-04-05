# Python Build for training, testing and exporting model

import numpy as np
import pandas as pd
import tensorflow as tf
import pickle

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM, Dropout, GRU, Bidirectional
from tensorflow.keras.optimizers import SGD, RMSprop
from tensorflow.keras.models import load_model

from sklearn.metrics import mean_squared_error
from sklearn.preprocessing import MinMaxScaler  

# Just disables the warning, doesn't enable AVX/FMA
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# Suppressing deprecated warnings
tf.logging.set_verbosity(tf.logging.ERROR)

window_size = 60

def getOptimizer(optimizer, lr, momentum):
    if optimizer == 0:
        return RMSprop(lr = lr)
    else:
        return SGD()

def getLSTMSequential(X_train):
    
    # The LSTM architecture
    regressor = Sequential()

    # First LSTM layer with Dropout regularisation
    regressor.add(LSTM(units=50, return_sequences=True, input_shape=(X_train.shape[1],1)))
    regressor.add(Dropout(0.2))
    
    # Second LSTM layer
    regressor.add(LSTM(units=50, return_sequences=True))
    regressor.add(Dropout(0.2))
    
    # Third LSTM layer
    regressor.add(LSTM(units=50, return_sequences=True))
    regressor.add(Dropout(0.2))
    
    # Fourth LSTM layer
    regressor.add(LSTM(units=50))
    regressor.add(Dropout(0.2))
    
    # The output layer
    regressor.add(Dense(units=1))
    
    return regressor

def getScaledData(training_set, scale, file_name):

    sc = MinMaxScaler(feature_range=(0,1))
    training_set_scaled = sc.fit_transform(training_set)
    
    pickle_out = open(file_name + '_scaler.pickle', 'wb')
    pickle.dump(sc, pickle_out)
    pickle_out.close()

    # creating a data structure with window_size timesteps and 1 output
    # for each element of training set, we have window_size previous training set elements 
    X_train = []
    Y_train = []
    for i in range(window_size,training_set_scaled.shape[0]):
        X_train.append(training_set_scaled[i-window_size:i,0])
        Y_train.append(training_set_scaled[i,0])
    X_train, Y_train = np.array(X_train), np.array(Y_train)

    # Reshaping X_train for efficient modelling
    X_train = np.reshape(X_train, (X_train.shape[0],X_train.shape[1],1))

    return X_train, Y_train

def train(training_set, date, lr, scale, epochs, momentum, optimizer, file_name):
    if(type(training_set) == list):
        
        # Constructing a pandas dataframe for reusability and reference
        df = pd.DataFrame(data = training_set, columns = ['Feature'], index = date)
        df.index.names = ['Date']
        df.index = pd.to_datetime(df.index)
        df.to_csv(file_name + '.csv')

        training_set = df.values

        # Scaling the training set
        X_train, Y_train = getScaledData(training_set, scale, file_name)
        
        # Constructing a stacked LSTM Sequential Model
        regressor = getLSTMSequential(X_train)

        # Compiling the RNN
        regressor.compile(optimizer=getOptimizer(optimizer, lr, momentum),loss='mean_squared_error')
        
        # Fitting to the training set
        regressor.fit(X_train, Y_train,epochs = epochs,batch_size=32)

        #Saving trained model
        regressor.save(file_name + '.h5')

        #Deleting model instance
        del regressor

        return 100
    
    else:
        return 110

def test(testing_set, date, file_name):
    if(type(testing_set) == list):

        # Constructing a pandas dataframe for reusability and reference
        df = pd.DataFrame(data = testing_set, columns = ['Feature'], index = date)
        df.index.names = ['Date']
        df.index = pd.to_datetime(df.index)

        prev_dataset = pd.read_csv(file_name + '.csv')

        regressor = load_model(file_name + '.h5')

        file = open(file_name + '_scaler.pickle', 'rb')
        scaler = pickle.load(file)

        predictions = []
        for i in range(df.shape[0]):
            predictions.append(regressor.predict(scaler.transform(pd.concat([prev_dataset.tail(window_size - i), predictions[:i]].values))))
        
        return 0

def predict(file_name):
    if(type(X) == list):

        dataset = pd.read_csv(file_name + '.csv', index_col='Date', parse_dates=['Date'])

        regressor = load_model(file_name + '.h5')

        file = open(file_name + '_scaler.pickle', 'rb')
        scaler = pickle.load(file)        