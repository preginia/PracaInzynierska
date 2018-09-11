#pragma once
#include "Perceptron.h"
#include "DecisionStump.h"
#include <vector>
#include<math.h>
#include <iostream>

#include "Classifier.h"
class AdaBoost
{
private:
	std::vector<Classifier*> classifiers;
	std::vector<Sample> listOfSamples;

	std::vector<double> alphas;
	std::vector<double> ada_weights;

	std::string localization;

	int iterations;

	int ClassiferIt;
	double LFACTOR;

	void FillDefaultWeights();
public:
	void DSBoost();
	void PerceptronBoost();
	void PerceptronMVBoost();
	double Classification(Sample sample);
	AdaBoost(vector<Sample> listOfSamples,int iterations,std::string localization,int ClassiferIt, double LFACTOR);
	~AdaBoost();

	std::string GetLocalization();

};

