#include "stdafx.h"
#include "DecisionStump.h"
#include <iostream>
#include <numeric>
#include <algorithm>


double DecisionStump::Classification(Sample sample)
{
	if (sample.getProperty(this->selected_feature) < this->threshold)
		return -1;
	else 
		return 1;
}

DecisionStump::DecisionStump(vector<Sample> samplesList, vector<double> &ada_weights, string localization) : Classifier(samplesList, localization)
{
	this->samplesList = samplesList;
	this->localization = localization;
	this->ada_weights = &ada_weights;

	threshold = 0; 
	selected_feature = 0;
}

DecisionStump::DecisionStump(vector<Sample> samplesList, string localization)  : Classifier(samplesList, localization)
{
	this->ada_weights = nullptr;

	threshold = 0;
	selected_feature = 0;
}

DecisionStump::~DecisionStump()
{
}

template<typename T>
inline void DecisionStump::sort_indexes(const vector<T>& X, vector<int>& idx)
{
	std::sort(idx.begin(), idx.end(),
		[&X](size_t i1, size_t i2) {return X[i1] < X[i2]; });
}

std::vector<double> DecisionStump::GetSamplesPropertiesAtIndex(int propertyIndex)
{
	vector<double> properties;

	for (int i = 0; i < this->samplesList.size(); i++)
	{
		Sample tmpSample = this->samplesList.at(i);
		properties.push_back(tmpSample.getProperties().at(propertyIndex));
	}

	return properties;
}


void DecisionStump::Learning()
{
	double current_err = HUGE_VAL;
	int parametersAmount = this->samplesList.at(0).getProperties().size();

	for (int i = 0; i < parametersAmount; i++)
	{
		vector<double> samples = GetSamplesPropertiesAtIndex(i);

		vector<int> Indices(this->samplesList.size());
		std::iota(Indices.begin(), Indices.end(), 0);
		
		sort_indexes(samples, Indices);

		for (int j = 0; j < samples.size() - 1; j++)
		{
			double err = 0.0;
			double thr = (samples[Indices[j]] + samples[Indices[j + 1]]) / 2;

			for (int k = 0; k < samples.size(); k++)
			{
				if ((samples[k] < thr && classes[k] != -1)
					|| (samples[k] >= thr && classes[k] != 1))
				{
					if (ada_weights)
						err += ada_weights->at(k);
					else
						err++;
				}
			}

			if (err < current_err)
			{
				current_err = err;
				this->threshold = thr;
				this->selected_feature = i;
			}
		}
	}
}

string DecisionStump::GetLocalization()
{
	return this->localization;
}
