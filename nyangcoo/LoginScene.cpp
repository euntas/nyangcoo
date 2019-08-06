#include "pch.h"
#include "LoginScene.h"

LoginScene::LoginScene() : Scene()
{
	Name = "Scene_Start";

	bg = new StaticObject();
	bg->AssetFileName = TEXT("bg.png");
	bg->rc = Rect(0, 0, 1080, 1920);

	Btn* StartBtn = new Btn();
	StartBtn->ID = eScene_Game;
	StartBtn->AssetFileName = TEXT("ed.jpg");
	StartBtn->rc = Rect(100, 100, 200, 150);

	Btn* ExitBtn = new Btn();
	ExitBtn->ID = eScene_Exit;
	ExitBtn->AssetFileName = TEXT("ed.jpg");
	ExitBtn->rc = Rect(100, 300, 200, 350);

	infoStaticObj.emplace_back(StartBtn);
	infoStaticObj.emplace_back(ExitBtn);
}

