#include "stdafx.h"
#include "IrisData.h"
#include "DatasFromFile.h"
#include "Localization.h"
#include <fstream>
#include<iostream>
#include <cstdlib>
#include <ctime>

bool IrisData::GetDatas(string path)
{
	ifstream dataFile;
	dataFile.open(path);

	if (dataFile.fail())
		return false;

	double a;
	double b;
	double c;
	double d;


	string loc;

	do {
		dataFile >> a;
		dataFile >> b;
		dataFile >> c;
		dataFile >> d;
		dataFile >> loc;

		vector<double> properties;

		properties.push_back(a);
		properties.push_back(b);
		properties.push_back(c);
		properties.push_back(d);
	


		Sample *patient = new Sample("", properties, loc);
		this->listOfPatients.push_back(*patient);


	} while (dataFile.peek() != EOF);



	return true;
}

IrisData::IrisData()
{
}


IrisData::~IrisData()
{
}
