#include "stdafx.h"
#include "OneVsAll.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

OneVsAll::OneVsAll(vector<Classifier*> classifiers)
{
	this->classifiers = classifiers;
}

string OneVsAll::Classification(Sample sample)
{	
	Classifier *predictedClassifer = this->classifiers[0];

	double maxValue = this->classifiers[0]->Classification(sample);

	for (auto classifer : classifiers)
	{
		double value = classifer->Classification(sample);


		if (value > maxValue)
		{
			maxValue = value;
			predictedClassifer = classifer;
		}
	}

	if (predictedClassifer)
		return predictedClassifer->GetLocalization();

	return "";

}


OneVsAll::~OneVsAll()
{
}
