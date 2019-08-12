#pragma once
#include "Scene.h"

class CookieSelectScene :
	public Scene
{
public:
	CookieSelectScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
};