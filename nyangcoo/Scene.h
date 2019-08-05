#pragma once
#include "framework.h"

using namespace std;

class Scene
{
public:
	void Start();
	void Loop(float Delta);
	void End();
	bool bLoop;
	CString Name;
	vector<Object*> info;
};

