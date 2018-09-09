#pragma once
#include "Patient.h"

class Classifier
{
protected:
	bool isLearned;
	std::string localization;
	vector<Sample> samplesList;
	void GenerateClasses();
public:
	Classifier(vector<Sample> samplesList, std::string localization);
	~Classifier();

	vector<int> classes;

	virtual void Learning() = 0;
	virtual double Classification(Sample sample) = 0;
	std::string GetLocalization();
};

