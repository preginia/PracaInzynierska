#include "stdafx.h"
#include "MultiVariantePerceptron.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void MultiVariantePerceptron::Learning()
{
	srand(time(NULL));
	int iterationsAmount = 300;
	this->learningFactor = 0.1;
	int minOfBadClassificatedSamples = samplesList.size();

	//cout << endl << "Percetron expected localizaton: " << this->localization << endl << endl;

	double current_err = HUGE_VAL;

	while (true)
	{
		int badClassificatedSamplesAmount = 0;
		vector<Sample> badClassificatedSamplesList;

		double err = 0.0;
		// Szukam tych próbek dla których które przy obecnych wagach perceptron Ÿle klasyfikuje
		for (int i = 0; i < this->samplesList.size(); i++)
		{
			Sample tmpSample = samplesList.at(i);
			double value = this->countWithWeights(tmpSample);

			if (IsSampleBadlyClassificated(value, classes[i]))
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
		if (badClassificatedSamplesAmount == 0 || iterationsAmount == 0)
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

double MultiVariantePerceptron::Classification(Sample sample)
{
	return countWithBestWeights(sample);
}

MultiVariantePerceptron::MultiVariantePerceptron(vector<Sample> sampleList, string localization) : Perceptron(sampleList, localization)
{
}

MultiVariantePerceptron::MultiVariantePerceptron(vector<Sample> samplesList, vector<double>& ada_weights, string localization) 
	: Perceptron(samplesList,ada_weights,localization)
{
}

MultiVariantePerceptron::~MultiVariantePerceptron()
{
}
