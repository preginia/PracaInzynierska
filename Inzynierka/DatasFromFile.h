#pragma once
#include <list>
#include "Patient.h"
#include<vector>
using namespace std;

class DatasFromFile
{
private:
	vector<Sample> listOfPatients;
	
public:

	static vector<Sample> GetRandomSamples(int amount, vector<Sample> &allSamples);
	DatasFromFile();
	~DatasFromFile();
	bool GetDatas(string path);
	void WriteList();
	vector<Sample> GetList();

};

