#pragma once
#include "Scene.h"

class LoadGameScene :
	public Scene
{
public:
	LoadGameScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
	StaticObject* selectedImg;
	Btn* SlotBtn[3];

	std::wstring tempTitleStr[ALL_STAGE_NUM];
};
