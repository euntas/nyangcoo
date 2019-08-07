#pragma once
#include "Scene.h"
class GameScene :
	public Scene
{
public:
	GameScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
};

