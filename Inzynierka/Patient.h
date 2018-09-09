#pragma once
#include <string>
#include<vector>

using namespace std;
class Sample 
{
private:
	string name;
	vector<double> properties;
	string localization;
	int expectedValue;
	
public:
	Sample(string name,
			vector<double>properties,
			string localization);
	~Sample();
	string getLozalization();
	double getProperty(int index);
	void setProperty(int index,double value);
	int getNumberOfProperites();
	vector<double> getProperties();
	void setLocalization(int value);
	void setExpectedValue(int expectedValue);
	int getExpectedValue();
	string GetName();
};

