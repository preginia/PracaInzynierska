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

	void FillDefaultWeights();
public:
	void DSBoost();
	void PerceptronBoost();
	double Classification(Sample sample);
	AdaBoost(vector<Sample> listOfSamples,int iterations,std::string localization);
	~AdaBoost();

	std::string GetLocalization();

};

