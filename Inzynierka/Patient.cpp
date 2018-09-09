#include "stdafx.h"
#include "Patient.h"
#include <string.h>





Sample::Sample(string name,vector<double> properties,string localization)
{
	this->name = name;
	this->properties = properties;
	this->localization = localization;
	this->expectedValue = 0;


}

Sample::~Sample()
{
}

string Sample::getLozalization()
{
	return this->localization;
}

double Sample::getProperty(int index)
{
	try 
	{
		return this->properties[index];
	}
	catch (exception) 
	{
		return -1;
	}
}

void Sample::setProperty(int index, double value)
{
	this->properties.at(index = value);
}

int Sample::getNumberOfProperites()
{
	return this->properties.size();
}

vector<double> Sample::getProperties()
{
	return this->properties;
}


void Sample::setLocalization(int value)
{
	this->localization = value;
}

void Sample::setExpectedValue(int expectedValue)
{
	this->expectedValue = expectedValue;
}

int Sample::getExpectedValue()
{
	return this->expectedValue;
}

string Sample::GetName()
{
	return this->name;
}
