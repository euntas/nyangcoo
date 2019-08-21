#pragma once
#include "Scene.h"
class SaveGameScene :
	public Scene
{
public:
	SaveGameScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
	StaticObject* selectedImg;
	int seletedSlotNum;

	std::wstring tempTitleStr[ALL_STAGE_NUM + 1];
};

