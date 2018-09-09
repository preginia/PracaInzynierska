#include "stdafx.h"
#include "AdaBoostOneVsAll.h"




AdaBoostOneVsAll::AdaBoostOneVsAll(vector<AdaBoost*> adaBoostList, int AdaItterations)
{
	this->AdaItterations = AdaItterations;
	this->adaBoostList = adaBoostList;
}

std::string AdaBoostOneVsAll::Classification(Sample sample)
{
	AdaBoost *predictedClassifer = adaBoostList[0];

	double maxValue = this->adaBoostList[0]->Classification(sample);

	for (auto adaBoost : adaBoostList)
	{
		double value = adaBoost->Classification(sample);

		if (value > maxValue)
		{
			maxValue = value;
			predictedClassifer = adaBoost;
		}
	}

	if (predictedClassifer)
		return predictedClassifer->GetLocalization();

	return "";
}

AdaBoostOneVsAll::~AdaBoostOneVsAll()
{
}
