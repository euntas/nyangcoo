#pragma once
#include "Scene.h"

class StartScene :
	public Scene
{
public:
	StartScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
};

