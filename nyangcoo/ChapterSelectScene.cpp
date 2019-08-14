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
	GameStartBtn->rc = Rect(0, 0, 277, 85);
	GameStartBtn->x = 1058;
	GameStartBtn->y = 550;

	Btn* CookieSelectBtn = new Btn();
	CookieSelectBtn->ID = eScene_CookieSelect;
	CookieSelectBtn->AssetFileName = TEXT("CookieSelect_btn.png");
	CookieSelectBtn->rc = Rect(0, 0, 204, 89);
	CookieSelectBtn->x = 49;
	CookieSelectBtn->y = 550;

	Btn* NextChapterBtn = new Btn();
	NextChapterBtn->ID = eScene_Start;
	NextChapterBtn->AssetFileName = TEXT("arrow_right.png");
	NextChapterBtn->rc = Rect(0, 0, 100, 118);
	NextChapterBtn->x = 1310;
	NextChapterBtn->y = 275;

	Btn* PrevChapterBtn = new Btn();
	PrevChapterBtn->ID = eScene_Start;
	PrevChapterBtn->AssetFileName = TEXT("arrow_left.png");
	PrevChapterBtn->rc = Rect(0, 0, 100, 118);
	PrevChapterBtn->x = 10;
	PrevChapterBtn->y = 275;

	Btn* ChapterTitle = new Btn();
	ChapterTitle->AssetFileName = TEXT("chapter_title.png");
	ChapterTitle->rc = Rect(0, 0, 553, 111);
	ChapterTitle->x = 470;
	ChapterTitle->y = 8;

	Btn* StageClearedBtn = new Btn();
	StageClearedBtn->ID = eScene_Game;
	StageClearedBtn->AssetFileName = TEXT("stage_cleared.png");
	StageClearedBtn->rc = Rect(0, 0, 113, 112);
	StageClearedBtn->x = 148;
	StageClearedBtn->y = 273;

	Btn* StageNotYetBtn1 = new Btn();
	//StageNotYetBtn1->ID = eScene_Game;
	StageNotYetBtn1->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn1->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn1->x = 347;
	StageNotYetBtn1->y = 273;

	Btn* StageNotYetBtn2 = new Btn();
	//StageNotYetBtn2->ID = eScene_Game;
	StageNotYetBtn2->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn2->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn2->x = 535;
	StageNotYetBtn2->y = 183;

	Btn* StageNotYetBtn3 = new Btn();
	//StageNotYetBtn3->ID = eScene_Game;
	StageNotYetBtn3->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn3->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn3->x = 535;
	StageNotYetBtn3->y = 368;

	Btn* StageNotYetBtn4 = new Btn();
	//StageNotYetBtn4->ID = eScene_Game;
	StageNotYetBtn4->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn4->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn4->x = 729;
	StageNotYetBtn4->y = 128;

	Btn* StageNotYetBtn5 = new Btn();
	//StageNotYetBtn5->ID = eScene_Game;
	StageNotYetBtn5->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn5->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn5->x = 729;
	StageNotYetBtn5->y = 424;

	Btn* StageNotYetBtn6 = new Btn();
	//StageNotYetBtn6->ID = eScene_Game;
	StageNotYetBtn6->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn6->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn6->x = 907;
	StageNotYetBtn6->y = 183;

	Btn* StageNotYetBtn7 = new Btn();
	//StageNotYetBtn7->ID = eScene_Game;
	StageNotYetBtn7->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn7->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn7->x = 907;
	StageNotYetBtn7->y = 368;

	Btn* StageNotYetBtn8 = new Btn();
	//StageNotYetBtn8->ID = eScene_Game;
	StageNotYetBtn8->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn8->rc = Rect(0, 0, 113, 112);
	StageNotYetBtn8->x = 1094;
	StageNotYetBtn8->y = 273;	


	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(GameStartBtn);
	infoStaticObj.emplace_back(CookieSelectBtn);
	infoStaticObj.emplace_back(NextChapterBtn);
	infoStaticObj.emplace_back(PrevChapterBtn);
	infoStaticObj.emplace_back(ChapterTitle);
	infoStaticObj.emplace_back(StageClearedBtn);
	infoStaticObj.emplace_back(StageNotYetBtn1);
	infoStaticObj.emplace_back(StageNotYetBtn2);
	infoStaticObj.emplace_back(StageNotYetBtn3);
	infoStaticObj.emplace_back(StageNotYetBtn4);
	infoStaticObj.emplace_back(StageNotYetBtn5);
	infoStaticObj.emplace_back(StageNotYetBtn6);
	infoStaticObj.emplace_back(StageNotYetBtn7);
	infoStaticObj.emplace_back(StageNotYetBtn8);

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