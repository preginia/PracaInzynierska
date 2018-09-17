#pragma once
#include "DatasFromFile.h"

class IrisData : public DatasFromFile
{
public:
	bool GetDatas(string path);
	IrisData();
	~IrisData();
};

