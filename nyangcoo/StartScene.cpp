#include "pch.h"
#include "StartScene.h"

StartScene::StartScene() : Scene()
{
	Name = "Scene_Start";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg.png");
	bg->rc = Rect(0, 0, 1420, 672);

	Btn* StartBtn = new Btn();
	StartBtn->ID = eScene_Game;
	StartBtn->AssetFileName = TEXT("title_btn_00.png");
	StartBtn->rc = Rect(0,0, 236, 72);
	StartBtn->x = 600;
	StartBtn->y = 200;

	Btn* ContinueBtn = new Btn();
	ContinueBtn->ID = eScene_Continue;
	ContinueBtn->AssetFileName = TEXT("title_btn_01.png");
	ContinueBtn->rc = Rect(0, 0, 236, 72);
	ContinueBtn->x = 600;
	ContinueBtn->y = 290;

	Btn* LoadGameBtn = new Btn();
	LoadGameBtn->ID = eScene_LoadGame;
	LoadGameBtn->AssetFileName = TEXT("title_btn_02.png");
	LoadGameBtn->rc = Rect(0, 0, 236, 72);
	LoadGameBtn->x = 600;
	LoadGameBtn->y = 380;

	Btn* ChallengeBtn = new Btn();
	ChallengeBtn->ID = eScene_Challenge;
	ChallengeBtn->AssetFileName = TEXT("title_btn_03.png");
	ChallengeBtn->rc = Rect(0, 0, 236, 72);
	ChallengeBtn->x = 600;
	ChallengeBtn->y = 470;

	Btn* ExitBtn = new Btn();
	ExitBtn->ID = eScene_Exit;
	ExitBtn->AssetFileName = TEXT("title_btn_04.png");
	ExitBtn->rc = Rect(0, 0, 236, 72);
	ExitBtn->x = 600;
	ExitBtn->y = 560;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(StartBtn);
	infoStaticObj.emplace_back(ContinueBtn);
	infoStaticObj.emplace_back(LoadGameBtn);
	infoStaticObj.emplace_back(ChallengeBtn);
	infoStaticObj.emplace_back(ExitBtn);
}

void StartScene::Init()
{

}

void StartScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void StartScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void StartScene::Release()
{

}

