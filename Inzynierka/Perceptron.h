#pragma once
#include "Patient.h"
#include <vector>
#include "Classifier.h"

class Perceptron : public Classifier
{
private:

	int _fet;
	double _weight;
	double _bias;




	vector<double> GetProperitesAt(int i);

protected:

	double countWithBestWeights(Sample patient);
	vector<double> weight;
	vector<double> bestWeight;


	vector<Sample> getListOfBadlyClassificatedSamples();
	vector<double> *ada_weights = nullptr;

	string positiveOneLocalization;
	double bias;
	double bestBias;
	int threshold;
	double learningFactor;
	int it;

	bool IsSampleBadlyClassificated(double value, int expectedValue);
	void ModifyWeights(Sample &randomBadSample);
	void WriteLearningStatus(int iterationsAmount, int badClassificatedSamplesAmount);
	void WriteLearningStatusInLastIteration(int iterationsAmount, int badClassificatedSamplesAmount);

	double countWithWeights(Sample patient);

public:
	void Learning() override;
	void Learning2();
	double Classification(Sample sample) override;

	double Classification2(Sample sample) ;
	Perceptron(vector<Sample> samplesList, vector<double> &ada_weights, string localization, int it, double learningFactor);
	Perceptron(vector<Sample> samplesList, string localization, int it, double learningFactor);

	~Perceptron();
	void writeWeights();
	int compare(double n1, double threshold);
	void generateExpectedValue(string name);
	string getPositiveOneLocalization();
};

