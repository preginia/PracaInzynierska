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
#include "MultiVariantePerceptron.h"


vector<int> BOOST = { 3,5,10,20,50,60,65,70,75,80,85 };

using namespace std;
const int IT = 500;
const double LFACTOR = 0.01;

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
	perceptrons.push_back(new Perceptron(sampleList, "cp",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "im",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "pp",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "imU",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "om",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "omL",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "imL",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "imS",IT,LFACTOR));
}

void PerceptronMVInit(vector<Classifier*> &perceptrons, vector<Sample> &sampleList)
{
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "cp",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "im",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "pp",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "imU",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "om",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "omL",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "imL",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "imS",IT,LFACTOR));
}

void ADAInit(vector<AdaBoost*> &adaBoost, vector<Sample> &sampleList, int AdaItterations)
{
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "cp",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "im",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "pp",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imU",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "om",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "omL",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imL",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "imS",IT,LFACTOR));
}

#define ADA_STEPS 5
int main()
{
	DatasFromFile *dataFromFile = new DatasFromFile();
	dataFromFile->GetDatas("ecoli.data.txt");
	vector<Sample> sampleList = dataFromFile->GetList();
	double percent;
	int AdaItterations;
	
	/*
	
	vector<Classifier*> decisionStumps;

	DSInit(decisionStumps,sampleList);
	
	for (auto classifier : decisionStumps)
	{
		classifier->Learning();
	}

	OneVsAll decisionStumpsOVA(decisionStumps);
	percent = Checking::PercentOfCorrectlyClassificatedSamples(decisionStumpsOVA, sampleList);

	cout << "DS with OVA\t\t\t\t" << percent;


	for (int i = 1; i <= 20; i++)
	{
		if (i > 10)
			AdaItterations = ADA_STEPS * i-40;
		else
			AdaItterations = i;

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
	*/
	vector<Classifier*> perceptrons;
	PerceptronInit(perceptrons, sampleList);

	for (auto classifier : perceptrons)
	{
		classifier->Learning();
	}

	OneVsAll perceptronsOVA(perceptrons);

	percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsOVA, sampleList);
	
	cout << endl<<endl<<endl<<"Perceptron with OVA\t\t\t"<< percent;
	
	

	
	for (auto i : BOOST)
	{
		AdaItterations =  i;


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
	
	vector<Classifier*> perceptronsMV;
	PerceptronMVInit(perceptronsMV, sampleList);

	for (auto classifier : perceptronsMV)
	{
		classifier->Learning();
	}

	OneVsAll perceptronsMVOVA(perceptronsMV);

	percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsMVOVA, sampleList);

	cout << endl << endl << endl << "Multi Variante Perceptron with OVA\t\t\t" << percent;




	for (auto i : BOOST)
	{
		AdaItterations = i;



		vector<AdaBoost*> perceptronsMVAdaBoost;
		ADAInit(perceptronsMVAdaBoost, sampleList, AdaItterations);


		for (auto ada : perceptronsMVAdaBoost)
		{
			ada->PerceptronMVBoost();
		}

		AdaBoostOneVsAll perceptronsAdaBoostOVA(perceptronsMVAdaBoost, AdaItterations);

		double percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsAdaBoostOVA, sampleList);

		cout << endl << "Multi Variante Perceptron boosted " << AdaItterations << " times with OVA\t" << percent;
	}

	getchar();

}

