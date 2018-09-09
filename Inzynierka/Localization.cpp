#include "stdafx.h"
#include "Localization.h"
#include <string>

using namespace std;
int Localization::GetLocalizationValue(string value)
{
	
	/*
	cp  (cytoplasm)                                    143
	im  (inner membrane without signal sequence)        77
	pp  (perisplasm)                                    52
	imU (inner membrane, uncleavable signal sequence)   35
	om  (outer membrane)                                20
	omL (outer membrane lipoprotein)                     5
	imL (inner membrane lipoprotein)                     2
	imS (inner membrane, cleavable signal sequence)      2
	*/

	if (value._Equal("cp"))
		return 143;

	if (value._Equal("im"))
		return 77;

	if (value._Equal("pp"))
		return 52;

	if (value._Equal("imU"))
		return 35;

	if (value._Equal("om"))
		return 20;

	if (value._Equal("omL"))
		return 5;

	if (value._Equal("imL") || value._Equal("imS"))
		return 2;

}



Localization::Localization()
{
}


Localization::~Localization()
{
}
