#include "stdafx.h"
#include "Perceptron.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



bool Perceptron::IsSampleBadlyClassificated(double value, int expectedValue)
{
	return (compare(value, this->threshold) != expectedValue);
}

void Perceptron::ModifyWeights(Sample & randomBadSample)
{
	bias += learningFactor*(randomBadSample.getExpectedValue() - countWithWeights(randomBadSample));
	for (int i = 0; i <weight.size(); i++)
		weight.at(i) += learningFactor*(randomBadSample.getExpectedValue() - countWithWeights(randomBadSample))*randomBadSample.getProperties().at(i);

}

void Perceptron::WriteLearningStatus(int iterationsAmount, int badClassificatedSamplesAmount)
{
	if (iterationsAmount % 100 == 0)
	{
		//cout << "Iterations left: " << iterationsAmount << " || " << "Bad classificcated samples: " << badClassificatedSamplesAmount << endl;
	}
}

void Perceptron::WriteLearningStatusInLastIteration(int iterationsAmount, int badClassificatedSamplesAmount)
{
	//cout << "Last iteration " << iterationsAmount << " || " << "Bad classificcated samples: " << badClassificatedSamplesAmount << endl;
}

void Perceptron::Learning()
{
	srand(time(NULL));
	int iterationsAmount = 600;
	int minOfBadClassificatedSamples = samplesList.size();

	//cout << endl << "Percetron expected localizaton: " << this->localization << endl << endl;

	double current_err = HUGE_VAL;

	while (true) 
	{
		int badClassificatedSamplesAmount = 0 ;
		vector<Sample> badClassificatedSamplesList;

		double err = 0.0;
		// Szukam tych próbek dla których które przy obecnych wagach perceptron Ÿle klasyfikuje
		for (int i = 0; i < this->samplesList.size(); i++) 
		{
			Sample tmpSample = samplesList.at(i);
			double value = this->countWithWeights(tmpSample);
			
			if (IsSampleBadlyClassificated(value,classes[i]))
			{
				badClassificatedSamplesList.push_back(tmpSample);
				if (ada_weights)
				{
					err += ada_weights->at(i);
				}
			}
		}

		try 
		{
			badClassificatedSamplesAmount = badClassificatedSamplesList.size();
		}
		catch (exception) 
		{
			 badClassificatedSamplesAmount = 0;
		}


		// W zale¿noœci czy u¿ywamy adaboosta warunkiem do zapamietania najlepszych wag 
		// jest iloœæ Ÿle sklasyfikowanych próbek lub err

		if (ada_weights == nullptr)
		{
			if (minOfBadClassificatedSamples > badClassificatedSamplesAmount) 
			{

				minOfBadClassificatedSamples = badClassificatedSamplesAmount;
				for (int i = 0; i < weight.size(); i++)
				{
					bestWeight.at(i) = weight.at(i);
				}

				bestBias = bias;
			}
		}
		else
		{
			if (err < current_err) {

				current_err = err;
				minOfBadClassificatedSamples = badClassificatedSamplesAmount;
				for (int i = 0; i < weight.size(); i++)
				{
					bestWeight.at(i) = weight.at(i);
				}

				bestBias = bias;
			}
		}
		// Konczê uczenie gdy wszystkie próbki s¹ dobrze klasyfikowane lub osi¹gniêto iloœæ iteracji
		if (badClassificatedSamplesAmount == 0 || iterationsAmount==0) 
		{
			WriteLearningStatusInLastIteration(iterationsAmount, minOfBadClassificatedSamples);
			break;
		}

		WriteLearningStatus(iterationsAmount, minOfBadClassificatedSamples);

		// Wœród Ÿle sklasyfikowanych próbkek losuje jedn¹ i na jej podstawie modyfikuje wagi
		int randomIndexOfBadClassificatedSample = std::rand() % badClassificatedSamplesAmount;
		Sample randomBadSample = badClassificatedSamplesList.at(randomIndexOfBadClassificatedSample);
		ModifyWeights(randomBadSample);

		iterationsAmount--;

	}
}

double Perceptron::Classification(Sample sample)
{
	return countWithBestWeights(sample);
}

double Perceptron::countWithWeights(Sample patient)
{
	double sum = 0;
	for (int i = 0; i < patient.getNumberOfProperites(); i++) {
		sum += patient.getProperties().at(i)*weight.at(i);
	}
	return sum+bias;
}

double Perceptron::countWithBestWeights(Sample patient)
{
	double sum = 0;
	for (int i = 0; i < patient.getNumberOfProperites(); i++) {
		sum += patient.getProperties().at(i)*bestWeight.at(i);
	}
	return sum + bestBias;
}

vector<Sample> Perceptron::getListOfBadlyClassificatedSamples()
{
	vector<Sample> badlyClassificatedSamples;
	for (int i = 0; i < this->samplesList.size(); i++)
	{
		Sample tmpPatient = samplesList.at(i);
		double value = this->countWithBestWeights(tmpPatient);

		if (IsSampleBadlyClassificated(value, tmpPatient.getExpectedValue()))
		{
			badlyClassificatedSamples.push_back(tmpPatient);
		}
	}
	return badlyClassificatedSamples;
}



Perceptron::Perceptron(vector<Sample> sampleList, string localization) : Classifier(sampleList,localization)
{
	this->samplesList = sampleList;

	//ustawienie domyœlej wagi dla ka¿dej próbki
	for (int i = 0; i < sampleList.at(0).getNumberOfProperites(); i++)
	{
		this->weight.push_back(1);
		this->bestWeight.push_back(1);
	}

	this->threshold = 0;
	this->learningFactor =0.2;
	this->localization = localization;

	ada_weights = nullptr;

	// ustawienie dla ka¿dej próbki oczekiwanej wartoœci, 1 dla próbek z klas¹ któr¹ ma rozpoznawaæ
	// dany percepton i -1 dla innych
	this->generateExpectedValue(localization);

}

Perceptron::Perceptron(vector<Sample> samplesList, vector<double> &ada_weights, string localization) : Classifier(samplesList,localization)
{
	this->samplesList = samplesList;

	//ustawienie domyœlej wagi dla ka¿dej próbki
	for (int i = 0; i < samplesList.at(0).getNumberOfProperites(); i++)
	{
		this->weight.push_back(1);
		this->bestWeight.push_back(1);
	}

	this->threshold = 0;
	this->learningFactor = 0.2;
	this->localization = localization;

	this->ada_weights = &ada_weights;

	// ustawienie dla ka¿dej próbki oczekiwanej wartoœci, 1 dla próbek z klas¹ któr¹ ma rozpoznawaæ
	// dany percepton i -1 dla innych
	this->generateExpectedValue(localization);
}

Perceptron::~Perceptron()
{
}

void Perceptron::writeWeights()
{
	for (int i = 0; i < weight.size(); i++) {
		cout << endl << endl;
		cout << weight.at(i) << endl;
	}

}

int Perceptron::compare(double n1, double threshold)
{
	if (n1 < threshold)
		return -1;
	else
		return 1;
}

void Perceptron::generateExpectedValue(string name)
{
	for (int i = 0; i < samplesList.size(); i++) {
		if (this->samplesList.at(i).getLozalization() == name)
			this->samplesList.at(i).setExpectedValue(1);
		else
			this->samplesList.at(i).setExpectedValue(-1);
	}
}

string Perceptron::getPositiveOneLocalization()
{
	return this->positiveOneLocalization;
}
