#include "stdafx.h"
#include "DatasFromFile.h"
#include "Localization.h"
#include <fstream>
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


vector<Sample> DatasFromFile::GetRandomSamples(int amount, vector<Sample> &allSamples)
{/*
	int smalestWeight = INT_MAX;
	for (auto sample : allSamples)
	{
		if (sample.weight < smalestWeight)
		{
			smalestWeight = sample.weight;
		}
	}

	vector<Sample> tmpSamplesListToRand;
	for (int i =0 ; i < allSamples.size() ; i++)
	{
		Sample *tmpSample = &allSamples.at(i);
		int tmpWeight = tmpSample->weight - smalestWeight + 1;

		for (int j = 0; j < tmpWeight; j++)
		{
			tmpSamplesListToRand.push_back(*tmpSample);
		}

	}
	cout << "AAAAAA: " << tmpSamplesListToRand.size();

	vector<Sample> returnSamplesList;

	for (int i = 0; i < amount; i++)
	{
		int size = tmpSamplesListToRand.size();
		int rand = (std::rand() % size);
		Sample tmpSample = tmpSamplesListToRand.at(rand);

		for (auto sample : returnSamplesList)
		{
			if (sample.GetName().compare(tmpSample.GetName()) == 0)
			{
				//i--;
				continue;
			}
		}
	
		returnSamplesList.push_back(tmpSample);

		int x = tmpSamplesListToRand.at(rand).weight;
		int o = 12;
	}
	
	return returnSamplesList;
	*/
	vector<Sample> vec;
	return vec;
}
DatasFromFile::DatasFromFile()
{
}


DatasFromFile::~DatasFromFile()
{
	
}

bool DatasFromFile::GetDatas(string path)
{
	ifstream dataFile;
	dataFile.open(path);

	if (dataFile.fail())
		return false;

	string name;
	double mcg;
	double gvh;
	double lip;
	double chg;
	double acc;
	double alm1;
	double alm2;
	string cp;
	
	do {
		dataFile >> name;
		dataFile >> mcg;
		dataFile >> gvh;
		dataFile >> lip;
		dataFile >> chg;
		dataFile >> acc;
		dataFile >> alm1;
		dataFile >> alm2;
		dataFile >> cp;

		vector<double> properties;

		properties.push_back(mcg);
		properties.push_back(gvh);
		properties.push_back(lip);
		properties.push_back(chg);
		properties.push_back(acc);
		properties.push_back(alm1);
		properties.push_back(alm2);
		
		
		Sample *patient = new Sample(name,properties,cp);
		this->listOfPatients.push_back(*patient);
		
		
	} while (dataFile.peek() != EOF);

	

	return true;
}

void DatasFromFile::WriteList()
{
	
	if (listOfPatients.size() != 0) 
	{
		for (int i = 0; i < listOfPatients.size(); i++) 
		{
			cout << listOfPatients[i].getLozalization()<<endl;
		}
	}
}

vector<Sample> DatasFromFile::GetList()
{
	return this->listOfPatients;
}
