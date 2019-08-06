#pragma once
#include "StaticObject.h"
class Btn : public StaticObject
{
public:
	Btn();

	void SendLButtonDown();
	int ID;
};

