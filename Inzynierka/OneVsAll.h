#pragma once
#include<vector>
#include"Perceptron.h"
#include "DecisionStump.h"
#include "Classifier.h"
class OneVsAll
{
private:
	vector<Classifier*> classifiers;
public:
	OneVsAll(vector<Classifier*> classifiers);
	string Classification(Sample sample);
	
	~OneVsAll();
};

