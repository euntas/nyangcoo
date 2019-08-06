#pragma once

using namespace std;

class Scene
{
public:
	void Start();
	void Loop(float Delta);
	void End();
	bool bLoop;
	CString Name;
	vector<Object*> infoObj;
	vector<StaticObject*> infoStaticObj;
};

