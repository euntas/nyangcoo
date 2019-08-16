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

	void printGold(int _gold, Gdiplus::Graphics* pGraphics);
	void printTitle(Gdiplus::Graphics* pGraphics);

	StaticObject* bg;

	int gold;

	float gsGoldDelta;			// 골드 증가 기준속도
	float gsGoldDeltaA;
};

