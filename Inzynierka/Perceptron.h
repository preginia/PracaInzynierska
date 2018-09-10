#pragma once
#include "Patient.h"
#include <vector>
#include "Classifier.h"

class Perceptron : public Classifier
{
private:
	vector<double> weight;
	vector<double> bestWeight;

	int _fet;
	double _weight;
	double _bias;

	vector<Sample> getListOfBadlyClassificatedSamples();
	vector<double> *ada_weights = nullptr;

	string positiveOneLocalization;
	double bias;
	double bestBias;
	int threshold;
	double learningFactor;

	bool IsSampleBadlyClassificated(double value, int expectedValue);
	void ModifyWeights(Sample &randomBadSample);
	void WriteLearningStatus(int iterationsAmount, int badClassificatedSamplesAmount);
	void WriteLearningStatusInLastIteration(int iterationsAmount, int badClassificatedSamplesAmount);

	double countWithWeights(Sample patient);
	double countWithBestWeights(Sample patient);


	vector<double> GetProperitesAt(int i);
public:
	void Learning() override;
	void Learning2();
	double Classification(Sample sample) override;

	double Classification2(Sample sample) ;
	Perceptron(vector<Sample> samplesList, vector<double> &ada_weights, string localization);
	Perceptron(vector<Sample> samplesList, string localization);

	~Perceptron();
	void writeWeights();
	int compare(double n1, double threshold);
	void generateExpectedValue(string name);
	string getPositiveOneLocalization();
};

