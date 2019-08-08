#include "pch.h"
#include "LoginScene.h"

LoginScene::LoginScene() : Scene()
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

	Btn* LoadBtn = new Btn();
	LoadBtn->ID = eScene_Load;
	LoadBtn->AssetFileName = TEXT("title_btn_02.png");
	LoadBtn->rc = Rect(0, 0, 236, 72);
	LoadBtn->x = 600;
	LoadBtn->y = 380;

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
	infoStaticObj.emplace_back(LoadBtn);
	infoStaticObj.emplace_back(ChallengeBtn);
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

