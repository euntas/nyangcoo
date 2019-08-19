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

	// TODO. �������� Ŭ���� ���� ����. ���߿� DB�� �Űܾ� ��
	map<int, bool> stageClearList;

	StaticObject* bg;
	StaticObject* ChapterTitle;
};