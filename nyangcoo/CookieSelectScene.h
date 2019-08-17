#pragma once
#include "Scene.h"

class CookieSelectScene :
	public Scene
{
public:
	CookieSelectScene();
	CookieSelectScene(std::string characterName);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void selectChar(std::string name);

	void makeBtn(EScene ID);

	StaticObject* bg;
	StaticObject* Selected_Kiwi;

	std::string NameStr;
};