#pragma once
#include "Scene.h"

class LoginScene :
	public Scene
{
public:
	LoginScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
};

