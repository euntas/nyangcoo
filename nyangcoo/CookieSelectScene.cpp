#include "pch.h"
#include "CookieSelectScene.h"

CookieSelectScene::CookieSelectScene() : Scene()
{
	Name = "Scene_CookieSelect";

	Init();
}

void CookieSelectScene::makeBtn(EScene ID)
{
	Btn* b = new Btn();
	b->ID = ID;
	b->AssetFileName = TEXT("SelectStart_btn.png");
	b->rc = Rect(0, 0, 403, 118);
	b->x = 600;
	b->y = 534;

	infoStaticObj.emplace_back(b);
}

void CookieSelectScene::Init()
{
	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("CookieSelect_bg.png");
	bg->rc = Rect(0, 0, 1420, 672);

	Btn* GameStartBtn = new Btn();
	GameStartBtn->ID = eScene_Game;
	GameStartBtn->AssetFileName = TEXT("SelectStart_btn.png");
	GameStartBtn->rc = Rect(0, 0, 403, 118);
	GameStartBtn->x = 59;
	GameStartBtn->y = 534;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(GameStartBtn);

	makeBtn(eScene_Game);
}

void CookieSelectScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void CookieSelectScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void CookieSelectScene::Release()
{

}