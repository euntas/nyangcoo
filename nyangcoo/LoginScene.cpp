#include "pch.h"
#include "LoginScene.h"

LoginScene::LoginScene() : Scene()
{
	Name = "Scene_Start";

	bg = new StaticObject();
	Image* bgImg = new Image(TEXT("Asset\\bg.png"));
	bg->Img = bgImg;
	bg->rc = Rect(0, 0, 1080, 1920);

	Image* cm = new Image(TEXT("Asset\\ed.jpg"));

	Btn* StartBtn = new Btn();
	StartBtn->ID = 0;
	StartBtn->Img = cm;
	StartBtn->rc = Rect(100, 100, 200, 150);

	Btn* ExitBtn = new Btn();
	ExitBtn->ID = 1;
	ExitBtn->Img = cm;
	ExitBtn->rc = Rect(100, 300, 200, 350);

	info.emplace_back(StartBtn);
	info.emplace_back(ExitBtn);
}

