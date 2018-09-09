#pragma once
#include "OneVsAll.h"
#include "AdaBoost.h"

class AdaBoostOneVsAll 
{
private:
	int AdaItterations;
	vector<AdaBoost*> adaBoostList;

public:
	AdaBoostOneVsAll(vector<AdaBoost*> adaBoostList,int AdaItterations);
	string Classification(Sample sample);
	~AdaBoostOneVsAll();
};

