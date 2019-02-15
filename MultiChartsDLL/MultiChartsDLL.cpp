// MultiChartsDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Python.h"
#include "stdafx.h"
#include "MultiChartsDLL.h"
#include <windows.h>
#include <tchar.h> 

MultiCharts::MultiCharts()
{
	intNumber = 10;
	doubleNumber = 902.21;
	stringData = new char[1000]();
	doubleArray = new double[10] ();
}

MultiCharts::~MultiCharts()
{
	delete doubleArray;
	delete stringData;
	doubleArray = NULL;
	stringData = NULL;
}

PyObject* myModuleString = PyUnicode_FromString((char*)"build");
PyObject* myModule = PyImport_Import(myModuleString);



void MultiCharts::SetIntNumber(int intNumber)
{
	this->intNumber = intNumber;
}

int MultiCharts::GetIntNumber()
{
	return this->intNumber;
}

double MultiCharts::GetDoubleNumber()
{
	return this->doubleNumber;
}

void MultiCharts::SetDoubleNumber(double number)
{
	this->doubleNumber = number;
}

void MultiCharts::InitStringData(int size)
{
	this->stringData = new char[size];
}
	
char* MultiCharts::GetStringData()
{
	return this->stringData	;
}

void MultiCharts::SetStringData(char* stringData)
{
	this->stringData = stringData;
}

double* MultiCharts::GetDoubleArray()
{
	return this->doubleArray;
}


void MultiCharts::InitDoubleArray(int size)
{
	this->doubleArray = new double[size];
}

void MultiCharts::SetDoubleArray(double* doubleArray)
{
	this->doubleArray = doubleArray;
}


char* MultiCharts::PrintText()
{
	
}

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

void SetIntNumber(MultiCharts* multiCharts, int intNumber)
{
	if (multiCharts != NULL) 
	{
		multiCharts->SetIntNumber(intNumber);
	}
}

int GetIntNumber(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->GetIntNumber();
	}
	return 0;
}

double GetDoubleNumber(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->GetDoubleNumber();
	}
	return 0.0;
}

char* GetStringData(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->GetStringData();
	}
	return NULL;
}

void InitStringData(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitStringData(size);
	}
}

double* GetDoubleArray(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->GetDoubleArray();
	}
	return NULL;
}

void SetDoubleNumber(MultiCharts* multiCharts, double doubleNumber)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetDoubleNumber(doubleNumber);
	}
}

void SetStringData(MultiCharts* multiCharts, char* stringData)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetStringData(stringData);
	}
}

void InitDoubleArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitDoubleArray(size);
	}
}

void SetDoubleArray(MultiCharts* multiCharts, double* doubleArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetDoubleArray(doubleArray);
	}

}