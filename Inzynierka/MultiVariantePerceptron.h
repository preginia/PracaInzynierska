#pragma once
#include "Perceptron.h"
class MultiVariantePerceptron : public Perceptron
{
public:

	void Learning() override;
	double Classification(Sample sample) override;
	MultiVariantePerceptron(vector<Sample> sampleList, string localization);
	MultiVariantePerceptron(vector<Sample> samplesList, vector<double> &ada_weights, string localization);
	~MultiVariantePerceptron();
};

