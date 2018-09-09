#include "stdafx.h"
#include "Classifier.h"


void Classifier::GenerateClasses()
{
	for (auto sample : samplesList)
	{
		if (localization == sample.getLozalization())
		{
			classes.push_back(1);
		}
		else
		{
			classes.push_back(-1);
		}
	}
}

Classifier::Classifier(vector<Sample> samplesList,std::string localization)
{
	this->samplesList = samplesList;
	this->localization = localization;
	isLearned = false;

	GenerateClasses();
}


Classifier::~Classifier()
{
}

std::string Classifier::GetLocalization()
{
	return this->localization;
}
