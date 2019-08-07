#include "pch.h"
#include "LoginScene.h"

LoginScene::LoginScene() : Scene()
{
	Name = "Scene_Start";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg.jpg");
	bg->rc = Rect(0, 0, 1173, 660);

	Btn* StartBtn = new Btn();
	StartBtn->ID = eScene_Game;
	StartBtn->AssetFileName = TEXT("ed.jpg");
	StartBtn->rc = Rect(600, 200, 200, 100);

	Btn* ExitBtn = new Btn();
	ExitBtn->ID = eScene_Exit;
	ExitBtn->AssetFileName = TEXT("ed.jpg");
	ExitBtn->rc = Rect(600, 500, 200, 150);

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(StartBtn);
	infoStaticObj.emplace_back(ExitBtn);
}

void LoginScene::Init()
{

}

void LoginScene::Update(float Delta)
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->Objtype == eObjectType_Player)
		{
			it->Update(Delta);
		}
	}
}

void LoginScene::Render(Graphics* pGraphics)
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->Objtype == eObjectType_Player)
		{
			it->Render(pGraphics);
		}
	}
}

void LoginScene::Release()
{

}

