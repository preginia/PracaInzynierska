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
#include "IrisData.h"


vector<int> BOOST = { 3,5,10,20,50,60,65,70,75,80,85 };

using namespace std;
int IT = 5000;
double LFACTOR = 0.0001;

using namespace std;

void DSInit(vector<Classifier*> &decisionStumps,vector<Sample> &sampleList)
{
	decisionStumps.push_back(new DecisionStump(sampleList, "Iris-setosa"));
	decisionStumps.push_back(new DecisionStump(sampleList, "Iris-versicolor"));
	decisionStumps.push_back(new DecisionStump(sampleList, "Iris-virginica"));

}

void PerceptronInit(vector<Classifier*> &perceptrons, vector<Sample> &sampleList)
{
	perceptrons.push_back(new Perceptron(sampleList, "Iris-setosa",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "Iris-versicolor",IT,LFACTOR));
	perceptrons.push_back(new Perceptron(sampleList, "Iris-virginica",IT,LFACTOR));

}

void PerceptronMVInit(vector<Classifier*> &perceptrons, vector<Sample> &sampleList)
{
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "Iris-setosa",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "Iris-versicolor",IT,LFACTOR));
	perceptrons.push_back(new MultiVariantePerceptron(sampleList, "Iris-virginica",IT,LFACTOR));
	
}

void ADAInit(vector<AdaBoost*> &adaBoost, vector<Sample> &sampleList, int AdaItterations)
{
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "Iris-setosa",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "Iris-versicolor",IT,LFACTOR));
	adaBoost.push_back(new AdaBoost(sampleList, AdaItterations, "Iris-virginica",IT,LFACTOR));

}

#define ADA_STEPS 5
int main()
{
	IrisData *dataFromFile = new IrisData();
	dataFromFile->GetDatas("iris.txt");
	vector<Sample> sampleList = dataFromFile->GetList();
	double percent;
	int AdaItterations;
	
	

	vector<Classifier*> decisionStumps;

	DSInit(decisionStumps, sampleList);

	for (auto classifier : decisionStumps)
	{
		classifier->Learning();
	}

	OneVsAll decisionStumpsOVA(decisionStumps);
	percent = Checking::PercentOfCorrectlyClassificatedSamples(decisionStumpsOVA, sampleList);

	cout << /*"DS with OVA\t\t\t\t" << */percent;


	for (auto i : BOOST)
	{

		AdaItterations = i;

		vector<AdaBoost*> DSAdaBoost;
		ADAInit(DSAdaBoost, sampleList, AdaItterations);


		for (auto ada : DSAdaBoost)
		{
			ada->DSBoost();
		}

		AdaBoostOneVsAll DSAdaBoostOVA(DSAdaBoost, AdaItterations);

		percent = Checking::PercentOfCorrectlyClassificatedSamples(DSAdaBoostOVA, sampleList);

		cout << endl <</* "DS boosted "<<AdaItterations<<" times with OVA\t\t" <<*/ percent;

	}



	vector<Classifier*> perceptrons;
	PerceptronInit(perceptrons, sampleList);

	for (auto classifier : perceptrons)
	{
		classifier->Learning();
	}

	OneVsAll perceptronsOVA(perceptrons);

	percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsOVA, sampleList);

	cout << endl <</*"Perceptron with OVA\t\t\t"<< *//*IT <<" " <<*/" " << percent;




	for (auto i : BOOST)
	{
		AdaItterations = i;


		vector<AdaBoost*> perceptronsAdaBoost;
		ADAInit(perceptronsAdaBoost, sampleList, AdaItterations);


		for (auto ada : perceptronsAdaBoost)
		{
			ada->PerceptronBoost();
		}

		AdaBoostOneVsAll perceptronsAdaBoostOVA(perceptronsAdaBoost, AdaItterations);

		double percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsAdaBoostOVA, sampleList);

		cout << endl <</* "Perceptron boosted " << AdaItterations << " times with OVA\t"<< */percent;
	}


	
	LFACTOR = 0.0001;
	vector<Classifier*> perceptronsMV;
	PerceptronMVInit(perceptronsMV, sampleList);

	for (auto classifier : perceptronsMV)
	{
		classifier->Learning();
	}

	OneVsAll perceptronsMVOVA(perceptronsMV);

	percent = Checking::PercentOfCorrectlyClassificatedSamples(perceptronsMVOVA, sampleList);

	cout << endl << endl << endl <</* "Multi Variante Perceptron with OVA\t\t\t" <<*/ percent;



	
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

		cout << endl << /*"Multi Variante Perceptron boosted " << AdaItterations << " times with OVA\t" <<*/ percent;
	}
	
	getchar();

}

