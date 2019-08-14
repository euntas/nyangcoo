#pragma once
#include "Scene.h"
#include "StaticObject.h"

class PopUp : 
	public StaticObject
{
public : 
	PopUp();
	PopUp(EPopup name);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	EPopup name;
	StaticObject* bg;
	vector<StaticObject*> infoStaticObj;
};

