#include "pch.h"
#include "CookieSelectScene.h"

CookieSelectScene::CookieSelectScene() : Scene()
{
	Name = "Scene_CookieSelect";

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
}

void CookieSelectScene::Init()
{

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