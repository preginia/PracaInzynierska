#include "stdafx.h"
#include "MultiVariantePerceptron.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void MultiVariantePerceptron::Learning()
{
	srand(time(NULL));
	int minOfBadClassificatedSamples = samplesList.size();

	//cout << endl << "Percetron expected localizaton: " << this->localization << endl << endl;

	double current_err = HUGE_VAL;

	while (true)
	{
		int badClassificatedSamplesAmount = 0;
		vector<Sample> badClassificatedSamplesList;

		double err = 0.0;
		// Szukam tych pr�bek dla kt�rych kt�re przy obecnych wagach perceptron �le klasyfikuje
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


		// W zale�no�ci czy u�ywamy adaboosta warunkiem do zapamietania najlepszych wag 
		// jest ilo�� �le sklasyfikowanych pr�bek lub err

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
		// Koncz� uczenie gdy wszystkie pr�bki s� dobrze klasyfikowane lub osi�gni�to ilo�� iteracji
		if (badClassificatedSamplesAmount == 0 || this->it == 0)
		{
			WriteLearningStatusInLastIteration(this->it, minOfBadClassificatedSamples);
			break;
		}

		WriteLearningStatus(this->it, minOfBadClassificatedSamples);

		// W�r�d �le sklasyfikowanych pr�bkek losuje jedn� i na jej podstawie modyfikuje wagi
		int randomIndexOfBadClassificatedSample = std::rand() % badClassificatedSamplesAmount;
		Sample randomBadSample = badClassificatedSamplesList.at(randomIndexOfBadClassificatedSample);
		ModifyWeights(randomBadSample);

		this->it--;

	}
}

double MultiVariantePerceptron::Classification(Sample sample)
{
	return countWithBestWeights(sample);
}

MultiVariantePerceptron::MultiVariantePerceptron(vector<Sample> sampleList, string localization, int it, double learningFactor) : Perceptron(sampleList, localization,  it,  learningFactor)
{
}

MultiVariantePerceptron::MultiVariantePerceptron(vector<Sample> samplesList, vector<double>& ada_weights, string localization, int it, double learningFactor)
	: Perceptron(samplesList,ada_weights,localization, it, learningFactor)
{
}

MultiVariantePerceptron::~MultiVariantePerceptron()
{
}
