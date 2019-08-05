#pragma once
#include "Object.h"
class Btn : public Object
{
public:
	Btn();

	void SendLButtonDown();
	int ID;
};

