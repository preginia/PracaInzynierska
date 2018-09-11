#include "stdafx.h"
#include "AdaBoost.h"
#include "MultiVariantePerceptron.h"


void AdaBoost::FillDefaultWeights()
{
	for (int i = 0; i < listOfSamples.size(); i++)
	{
		ada_weights.push_back((double)1 / listOfSamples.size());
	}
}

void AdaBoost::DSBoost()
{
	for (int i = 0; i < iterations; i++)
	{
		Classifier *cls = new DecisionStump(listOfSamples, ada_weights, localization);
		cls->Learning();

		double err = 0;
		double alpha;


		//for samples{ if (out[i] != class[i]) sum += w[i] }
		//err = sum((out != class) * W)

		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			int out = cls->Classification(sample);

			if (out != cls->classes[i])
				err += ada_weights.at(i);
		}

		double p = (1.0 - err) / err;

		if (err == 0)
		{
			alpha = 0.0;
		}
		else
		{
			alpha = 0.5 * log(p);
		}

		double newWeightsSum = 0;


		// if out[i] != class[i] to W[i] = W[i] * exp(alfa),
		// else W[i] = W[i] * exp(-1 * alfa)

		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			int out = cls->Classification(sample) ;
			
			if (out != cls->classes[i])
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(alpha);
			}
			else
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(-1 * alpha);
			}

			newWeightsSum += ada_weights.at(i);
		}

		// W[i] = W[i] / sumW

		for (int i = 0; i < listOfSamples.size(); i++)
		{
			ada_weights.at(i) = ada_weights.at(i) / newWeightsSum;
		}

		classifiers.push_back(cls);
		alphas.push_back(alpha);
	}

	double alpha_sum = 0.0;
	for (int i = 0; i < alphas.size(); i++)
		alpha_sum += abs(alphas.at(i));
	for (int i = 0; i < alphas.size(); i++)
		alphas.at(i) /= alpha_sum;
}

void AdaBoost::PerceptronBoost()
{
	for (int i = 0; i < iterations; i++)
	{
		Classifier *cls = new Perceptron(listOfSamples, ada_weights, localization);
		cls->Learning();

		double err = 0;
		double alpha;


		//for samples{ if (out[i] != class[i]) sum += w[i] }
		//err = sum((out != class) * W)
		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			Perceptron *perceptron = dynamic_cast<Perceptron*>(cls);
			int out = perceptron->Classification(sample);
			out = perceptron->compare(perceptron->Classification(sample), 0);

			if (out != perceptron->classes[i])
				err += ada_weights.at(i);
		}

		double p = (1.0 - err) / err;

		if (err == 0)
		{
			alpha = 0.0;
		}
		else
		{
			alpha = 0.5 * log(p);
		}

		double newWeightsSum = 0;

		// if out[i] != class[i] to W[i] = W[i] * exp(alfa),
		// else W[i] = W[i] * exp(-1 * alfa)
		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			Perceptron *perceptron = dynamic_cast<Perceptron*>(cls);
			int out = perceptron->Classification(sample);
			out = perceptron->compare(perceptron->Classification(sample), 0);

			if (out != perceptron->classes[i])
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(alpha);
			}
			else
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(-1 * alpha);
			}

			newWeightsSum += ada_weights.at(i);
		}

		// W[i] = W[i] / sumW

		for (int i = 0; i < listOfSamples.size(); i++)
		{
			ada_weights.at(i) = ada_weights.at(i) / newWeightsSum;
		}

		classifiers.push_back(cls);
		alphas.push_back(alpha);
	}

	double alpha_sum = 0.0;
	for (int i = 0; i < alphas.size(); i++)
		alpha_sum += abs(alphas.at(i));
	for (int i = 0; i < alphas.size(); i++)
		alphas.at(i) /= alpha_sum;
}



void AdaBoost::PerceptronMVBoost()
{
	for (int i = 0; i < iterations; i++)
	{
		Classifier *cls = new MultiVariantePerceptron(listOfSamples, ada_weights, localization);
		cls->Learning();

		double err = 0;
		double alpha;


		//for samples{ if (out[i] != class[i]) sum += w[i] }
		//err = sum((out != class) * W)
		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			MultiVariantePerceptron *perceptron = dynamic_cast<MultiVariantePerceptron*>(cls);
			int out = perceptron->Classification(sample);
			out = perceptron->compare(perceptron->Classification(sample), 0);

			if (out != perceptron->classes[i])
				err += ada_weights.at(i);
		}

		double p = (1.0 - err) / err;

		if (err == 0)
		{
			alpha = 0.0;
		}
		else
		{
			alpha = 0.5 * log(p);
		}

		double newWeightsSum = 0;

		// if out[i] != class[i] to W[i] = W[i] * exp(alfa),
		// else W[i] = W[i] * exp(-1 * alfa)
		for (int i = 0; i < listOfSamples.size(); i++)
		{
			Sample sample = listOfSamples.at(i);
			MultiVariantePerceptron *perceptron = dynamic_cast<MultiVariantePerceptron*>(cls);
			int out = perceptron->Classification(sample);
			out = perceptron->compare(perceptron->Classification(sample), 0);

			if (out != perceptron->classes[i])
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(alpha);
			}
			else
			{
				ada_weights.at(i) = ada_weights.at(i) * exp(-1 * alpha);
			}

			newWeightsSum += ada_weights.at(i);
		}

		// W[i] = W[i] / sumW

		for (int i = 0; i < listOfSamples.size(); i++)
		{
			ada_weights.at(i) = ada_weights.at(i) / newWeightsSum;
		}

		classifiers.push_back(cls);
		alphas.push_back(alpha);
	}

	double alpha_sum = 0.0;
	for (int i = 0; i < alphas.size(); i++)
		alpha_sum += abs(alphas.at(i));
	for (int i = 0; i < alphas.size(); i++)
		alphas.at(i) /= alpha_sum;
}

double AdaBoost::Classification(Sample sample)
{
	
	double out = 0.0;

	for (int i = 0; i < iterations; i++)
	{
		double y = classifiers.at(i)->Classification(sample);

		out += alphas.at(i) * y;

	}

	return out;
}

AdaBoost::AdaBoost(vector<Sample> listOfSamples,int iterations,std::string localization)
{
	this->localization = localization;
	this->iterations = iterations;
	this->listOfSamples = listOfSamples;

	FillDefaultWeights();
}

AdaBoost::~AdaBoost()
{
}

std::string AdaBoost::GetLocalization()
{
	return localization;
}
