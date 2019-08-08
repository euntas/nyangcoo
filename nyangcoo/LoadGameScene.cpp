#include "pch.h"
#include "LoadGameScene.h"

LoadGameScene::LoadGameScene() : Scene()
{
	Name = "Scene_LoadGame";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("load_bg.png");
	bg->rc = Rect(0, 0, 1420, 672);

	Btn* LoadGameBtn = new Btn();
	LoadGameBtn->ID = eScene_Game;
	LoadGameBtn->AssetFileName = TEXT("load_btn.png");
	LoadGameBtn->rc = Rect(0, 0, 200, 60);
	LoadGameBtn->x = 1200;
	LoadGameBtn->y = 550;

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	BackTitleBtn->AssetFileName = TEXT("back_btn.png");
	BackTitleBtn->rc = Rect(0, 0, 200, 60);
	BackTitleBtn->x = 900;
	BackTitleBtn->y = 550;

	Btn* DeleteGameBtn = new Btn();
	DeleteGameBtn->ID = eScene_DeleteGame;
	DeleteGameBtn->AssetFileName = TEXT("delete_btn.png");
	DeleteGameBtn->rc = Rect(0, 0, 200, 60);
	DeleteGameBtn->x = 10;
	DeleteGameBtn->y = 550;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(LoadGameBtn);
	infoStaticObj.emplace_back(BackTitleBtn);
	infoStaticObj.emplace_back(DeleteGameBtn);
}

void LoadGameScene::Init()
{

}

void LoadGameScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void LoadGameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void LoadGameScene::Release()
{

}