#pragma once
#include "Scene.h"

class ScriptScene :
	public Scene
{
public:
	ScriptScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void printChoice(Gdiplus::Graphics* pGraphics);

	StaticObject* bg;
	StaticObject* ChapterName;
	StaticObject* ScriptText;
	StaticObject* ScriptChoice;
	StaticObject* ScriptPlayer;
};

