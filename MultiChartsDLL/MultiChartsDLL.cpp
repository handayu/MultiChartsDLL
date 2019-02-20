// MultiChartsDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Python.h"
#include "stdafx.h"
#include "MultiChartsDLL.h"
#include "pyhelper.hpp"

MultiCharts::MultiCharts()
{

}

MultiCharts::~MultiCharts()
{
	delete trainingData;
	delete dateArray;
	delete fileName;
	delete volumeArray;

	trainingData = NULL;
	dateArray = NULL;
	fileName = NULL;
	volumeArray = NULL;
}

/*

		--Member Functions--

*/

/*
char* MultiCharts::GetPythonStringData()
{
	CPyInstance hInstance;

	//CPyObject pName = PyUnicode_FromString("build");
	CPyObject pModule = PyImport_ImportModule("build");
	if (pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "getRandomText");
		if (pFunc)
		{
			CPyObject pValue = PyObject_CallObject(pFunc, NULL);
			pythonStringData = PyUnicode_AsUTF8(pValue);
			return pythonStringData;
		}
		else 
		{
			pythonStringData = new char[4] {"101"};
			return pythonStringData;
		}
	}
	else
	{
		pythonStringData = new char[4] {"102"};
		return pythonStringData;
	}
}
*/

void MultiCharts::InitTrainingData(int size)
{
	this->trainingDataSize = size;
}

void MultiCharts::SetTrainingData(double* trainingData)
{
	this->trainingData = trainingData;
}

void MultiCharts::InitDateArray(int size)
{
	this->dateArray = new char[size][DATE_SIZE];
}

void MultiCharts::SetDateArray(char (*dateArray)[DATE_SIZE])
{
	this->dateArray = dateArray;
}

void MultiCharts::InitVolumeArray(int size)
{
	this->volumeArray = new long[size];
}

void MultiCharts::SetVolumeArray(long* volume)
{
	this->volumeArray = volume;
}

void MultiCharts::InitFileName(int size)
{
	this->fileName = new char[size];
}

void MultiCharts::SetFileName(char* fileName)
{
	this->fileName = fileName;
}

void MultiCharts::SetLearningRate(double learningRate)
{
	this->learningRate = learningRate;
}

void MultiCharts::SetEpochs(short epochs)
{
	this->epochs = epochs;
}

void MultiCharts::SetScale(int scale)
{
	this->scale = scale;
}

void MultiCharts::SetOptimizer(short optimizer)
{
	this->optimizer = optimizer;
}

void MultiCharts::TrainModel()
{
	CPyInstance pyInstance;

	CPyObject pModule = PyImport_ImportModule("python-build\\MultiChartsBuild");
	if (pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "train");
		if (pFunc)
		{
			PyObject* argList = Py_BuildValue("O&", );
			CPyObject pValue = PyObject_CallObject(pFunc, argList);
		}
	}
}

/*

		-- Exported Functions -- 

*/

MultiCharts* CreateMultiCharts()
{
	return new MultiCharts();
}

void DisposeMultiCharts(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		delete multiCharts;
		multiCharts = NULL;
	}
}

void InitTrainingData(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetTrainingData(MultiCharts* multiCharts, double* trainingData)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetTrainingData(trainingData);
	}
}

void InitDateArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetDateArray(MultiCharts* multiCharts, char(*dateArray)[DATE_SIZE])
{
	if (multiCharts != NULL)
	{
		multiCharts->SetDateArray(dateArray);
	}
}

void InitVolumeArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetVolumeArray(MultiCharts* multiCharts, long * volumeArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetVolumeArray(volumeArray);
	}
}

void InitFileName(MultiCharts * multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetFileName(MultiCharts* multiCharts, char * fileName)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetFileName(fileName);
	}
}

void SetLearningRate(MultiCharts* multiCharts, double learningRate)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetLearningRate(learningRate);
	}
}

void SetEpochs(MultiCharts* multiCharts, short epochs)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetEpochs(epochs);
	}
}

void SetScale(MultiCharts* multiCharts, int scale)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetScale(scale);
	}
}

void SetOptimizer(MultiCharts* multiCharts, short optimizer)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetOptimizer(optimizer);
	}
}