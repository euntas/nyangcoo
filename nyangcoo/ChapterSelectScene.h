#pragma once
#include "Scene.h"

class ChapterSelectScene :
	public Scene
{
public:
	ChapterSelectScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	StaticObject* bg;
	StaticObject* ChapterTitle;
};