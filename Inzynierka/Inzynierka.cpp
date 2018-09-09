#include "stdafx.h"
#include "Patient.h"
#include<iostream>
#include "DatasFromFile.h"
#include "DecisionStump.h"
#include "Perceptron.h"
#include "OneVsAll.h"
#include "Checking.h"
#include <cstdlib>
#include <ctime>
#include "AdaBoost.h"
#include "AdaBoostOneVsAll.h"

using namespace std;

void DSInit(vector<Classifier*> &decisionStumps,vector<Sample> &sampleList)
{
	decisionStumps.push_back(new DecisionStump(sampleList, "cp"));
	decisionStumps.push_back(new DecisionStump(sampleList, "im"));
	decisionStumps.push_back(new DecisionStump(sampleList, "pp"));
	decisionStumps.push_back(new DecisionStump(sampleList, "imU"));
	decisionStumps.push_back(new DecisionStump(sampleList, "om"));
	decisionStumps.push_back(new DecisionStump(sampleList, "omL"));
	decisionStumps.push_back(new DecisionStump(sampleList, "imL"));
	decisionStumps.push_back(new DecisionStump(sampleList, "imS"));
}

void PerceptronInit(vector<Classifier*> &perceptrons, vector<Sample> &sampleList)
{
	perceptrons.push_back(new Perceptron(sampleList, "cp"));
	perceptrons.push_back(new Perceptron(sampleList, "im"));
	perceptrons.push_back(new Perceptron(sampleList, "pp"));
	perceptrons.push_back(new Perceptron(sampleList, "imU"));
	perceptrons.push_back(new Perceptron(sampleList, "om"));
	perceptrons.push_back(new Perceptron(sampleList, "omL"));
	perceptrons.push_back(new Perceptron(sampleList, "imL"));
	perceptrons.push_back(new Perceptron(sampleList, "imS"));
}

void ADAInit(vector<AdaBoost*> &adaBoost, vector<Sample> &sampleList, int AdaItterations)
{
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "cp"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "im"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "pp"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imU"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "om"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "omL"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imL"));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imS"));
}

#define ADA_STEPS 5
int main()
{
	DatasFromFile *dataFromFile = new DatasFromFile();
	dataFromFile->GetDatas("ecoli.data.txt");
	vector<Sample> sampleList = dataFromFile->GetList();
	double percent;
	int AdaItterations;
	
	
	
	vector<Classifier*> decisionStumps;

	DSInit(decisionStumps,sampleList);
	
	for (auto classifier : decisionStumps)
	{
		classifier->Learning();
	}

	OneVsAll decisionStumpsOVA(decisionStumps);
	percent = Checking::PercentOfCorrectlyClassificatedSamples(decisionStumpsOVA, sampleList);

	cout << "DS with OVA\t\t\t\t" << percent;


	for (int i = 1; i <= 15; i++)
	{
		AdaItterations = ADA_STEPS * i;

		vector<AdaBoost*> DSAdaBoost;
		ADAInit(DSAdaBoost, sampleList, AdaItterations);


		for (auto ada : DSAdaBoost)
		{
			ada->DSBoost();
		}

		AdaBoostOneVsAll DSAdaBoostOVA(DSAdaBoost, AdaItterations);

		percent = Checking::PercentOfCorrectlyClassificatedSamples(DSAdaBoostOVA, sampleList);

		cout << endl << "DS boosted "<<AdaItterations<<" times with OVA\t\t" << percent;

	}
	
	vector<Classifier*> perceptrons;
	PerceptronInit(perceptrons, sampleList);

	for (auto classifier : perceptrons)
	{
		classifier->Learning();
	}

	OneVsAll perceptronsOVA(perceptrons);

	percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsOVA, sampleList);
	
	cout << endl<<endl<<endl<<"Perceptron with OVA\t\t\t"<< percent;

	

	
	for (int i = 1; i <= 15; i++)
	{
		AdaItterations =  ADA_STEPS * i;

		vector<AdaBoost*> perceptronsAdaBoost;
		ADAInit(perceptronsAdaBoost, sampleList, AdaItterations);


		for (auto ada : perceptronsAdaBoost)
		{
			ada->PerceptronBoost();
		}

		AdaBoostOneVsAll perceptronsAdaBoostOVA(perceptronsAdaBoost, AdaItterations);

		double percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsAdaBoostOVA, sampleList);

		cout << endl << "Perceptron boosted " << AdaItterations << " times with OVA\t"<< percent;
	}

	getchar();

}

