#include "pch.h"
#include "ChapterSelectScene.h"

ChapterSelectScene::ChapterSelectScene() : Scene()
{
	Name = "Scene_ChapterSelect";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("ChapterSelect_bg.png");
	bg->rc = Rect(0, 0, 1420, 672);

	Btn* GameStartBtn = new Btn();
	GameStartBtn->ID = eScene_Game;
	GameStartBtn->AssetFileName = TEXT("GameStart_btn.png");
	GameStartBtn->rc = Rect(0, 0, 326, 132);
	GameStartBtn->x = 1044;
	GameStartBtn->y = 500;

	Btn* CookieSelectBtn = new Btn();
	CookieSelectBtn->ID = eScene_Start;
	CookieSelectBtn->AssetFileName = TEXT("CookieSelect_btn.png");
	CookieSelectBtn->rc = Rect(0, 0, 326, 132);
	CookieSelectBtn->x = 50;
	CookieSelectBtn->y = 500;

	Btn* NextChapterBtn = new Btn();
	NextChapterBtn->ID = eScene_Start;
	NextChapterBtn->AssetFileName = TEXT("arrow_right.png");
	NextChapterBtn->rc = Rect(0, 0, 100, 118);
	NextChapterBtn->x = 1270;
	NextChapterBtn->y = 275;

	Btn* PrevChapterBtn = new Btn();
	PrevChapterBtn->ID = eScene_Start;
	PrevChapterBtn->AssetFileName = TEXT("arrow_left.png");
	PrevChapterBtn->rc = Rect(0, 0, 100, 118);
	PrevChapterBtn->x = 50;
	PrevChapterBtn->y = 275;


	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(GameStartBtn);
	infoStaticObj.emplace_back(CookieSelectBtn);
	infoStaticObj.emplace_back(NextChapterBtn);
	infoStaticObj.emplace_back(PrevChapterBtn);
}

void ChapterSelectScene::Init()
{

}

void ChapterSelectScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void ChapterSelectScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void ChapterSelectScene::Release()
{

}