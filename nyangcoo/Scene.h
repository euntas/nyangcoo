#pragma once

using namespace std;

class Scene
{
public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();
	bool bLoop;
	CString Name;
	vector<Object*> infoObj;
	vector<StaticObject*> infoStaticObj;
};

