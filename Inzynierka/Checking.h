#pragma once

#include "OneVsAll.h"
#include "Patient.h"
#include "Perceptron.h"
#include <vector>
#include <iostream>
#include "DecisionStump.h"
#include "AdaBoostOneVsAll.h"
#include "Classifier.h"

class Checking
{
private:
	vector<Perceptron*> listOfPerceptrons;
	vector<DecisionStump*> listOfDecisionStumps;
	vector<Sample> *samplesList;
	bool AreLocalizationTheSame(string localization1, string localization2);
	void checkPerceptrons();
	void checkDesicionStumps();
	
public:
	static double PercentOfCorrectlyClassificatedSamples(AdaBoostOneVsAll adaboosts, vector<Sample> samplesList);
	static double PercentOfCorrectlyClassificatedSamples(OneVsAll OVA, vector<Sample> samplesList);
	Checking(vector<DecisionStump*> listOfDecisionStumps, vector<Perceptron*> listOfPerceptrons, vector<Sample> &samplesList);
	~Checking();
	int checkLearningResultsWithOneVsAll();
	static int min;
};

