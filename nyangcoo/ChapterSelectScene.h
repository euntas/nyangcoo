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

	// TODO. 스테이지 클리어 정보 관련. 나중에 DB로 옮겨야 함
	map<int, bool> stageClearList;

	StaticObject* bg;
	StaticObject* ChapterTitle;
};