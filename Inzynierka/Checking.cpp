#include "stdafx.h"
#include "Checking.h"



/*
void Checking::checkPerceptrons()
{
	OneVsAll *oneVsAll = new OneVsAll(listOfPerceptrons);

	int badClasificatedSampleCounter = 0;

	for (int i = 0; i < samplesList->size(); i++)
	{
		Sample *sample = &samplesList->at(i);
		string samplePredictionLocalization = oneVsAll->PerceptronsClassification(*sample);
		string sampleLocalization = sample->getLozalization();
		if (samplePredictionLocalization != sampleLocalization)
		{
			badClasificatedSampleCounter++;
		}
		else
		{
			//TODO
		}
	}
	cout << endl << "-----PERCEPTRONY---- " << endl;
	cout << endl << "Zle sklasyfikowane: " << badClasificatedSampleCounter;
	cout << endl << "Ilosc probek: " << samplesList->size();
	cout << endl << "Procent dobrze sklasyfikowanych: " << 100.0 - ((double)badClasificatedSampleCounter / samplesList->size()*100.0);

}

void Checking::checkDesicionStumps()
{
	OneVsAll *oneVsAll = new OneVsAll(listOfDecisionStumps);

	int badClasificatedSampleCounter = 0;

	for (int i = 0; i < samplesList->size(); i++)
	{
		Sample *sample = &samplesList->at(i);
		string samplePredictionLocalization = oneVsAll->DecisionStumpsClassification(*sample);
		string sampleLocalization = sample->getLozalization();
		if (samplePredictionLocalization != sampleLocalization)
		{
			badClasificatedSampleCounter++;
		}
		else
		{
			//TODO
		}
	}

	cout << endl << "-----DECISION STUMPS---- " << endl;
	cout << endl << "Zle sklasyfikowane: " << badClasificatedSampleCounter;
	cout << endl << "Ilosc probek: " << samplesList->size();
	cout << endl << "Procent dobrze sklasyfikowanych: " << 100.0 - ((double)badClasificatedSampleCounter / samplesList->size()*100.0);

}

Checking::Checking(vector<DecisionStump*> listOfDecisionStumps, vector<Perceptron*> listOfPerceptrons, vector<Sample> &samplesList)
{
	this->listOfPerceptrons = listOfPerceptrons;
	this->samplesList = &samplesList;
	this->listOfDecisionStumps = listOfDecisionStumps;
}

Checking::~Checking()
{
}

int Checking::checkLearningResultsWithOneVsAll()
{
	checkDesicionStumps();
	checkPerceptrons();
	return 1;
}*/

double Checking::PercentOfCorrectlyClassificatedSamples(AdaBoostOneVsAll adaboosts, vector<Sample> samplesList)
{
	int counter = 0;
	for (auto sample : samplesList)
	{
		if (adaboosts.Classification(sample) == sample.getLozalization())
		{
			counter++;
		}
	}

	return ((double)counter / samplesList.size() * 100);
}

double Checking::PercentOfCorrectlyClassificatedSamples(OneVsAll OVA, vector<Sample> samplesList)
{
	int counter = 0;
	for (auto sample : samplesList)
	{
		if (OVA.Classification(sample) == sample.getLozalization())
		{
			counter++;
		}
	}

	return ((double)counter / samplesList.size() * 100);
}
