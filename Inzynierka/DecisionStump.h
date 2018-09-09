#pragma once
#include"Patient.h"
#include<vector>
#include "Classifier.h"

class DecisionStump : public Classifier
{
private:
	double threshold;
	int selected_feature;
	vector<double> *ada_weights;

	template <typename T>
	void sort_indexes(const vector<T> &X, vector<int> &idx);
	vector<double> GetSamplesPropertiesAtIndex(int propertyIndex);

public:
	double Classification(Sample sample) override;
	DecisionStump(vector<Sample> listOfPatients,vector<double> &ada_weights, string localization);
	DecisionStump(vector<Sample> listOfPatients, string localization);
	~DecisionStump();
	void Learning();
	string GetLocalization();

};
	
