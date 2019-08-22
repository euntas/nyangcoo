#include "pch.h"
#include "ChapterSelectScene.h"

ChapterSelectScene::ChapterSelectScene() : Scene()
{
	Name = "Scene_ChapterSelect";

	Init();
}

void ChapterSelectScene::Init()
{
	infoStaticObj.clear();

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("ChapterSelect_bg.png");
	bg->ImgRC = Rect(0, 0, 1420, 672);
	bg->ViewRC = bg->ImgRC;

	Btn* GameStartBtn = new Btn();
	GameStartBtn->ID = eScene_Start;
	GameStartBtn->AssetFileName = TEXT("BackMain_btn.png");
	GameStartBtn->ImgRC = Rect(0, 0, 200, 173);
	GameStartBtn->ViewRC = GameStartBtn->ImgRC;
	GameStartBtn->x = 1187;
	GameStartBtn->y = 466;

	Btn* SaveGameBtn = new Btn();
	SaveGameBtn->ID = eSaveLoadBtn_Save;
	SaveGameBtn->AssetFileName = TEXT("saveload\\SaveGame_btn.png");
	SaveGameBtn->ImgRC = Rect(0, 0, 200, 158);
	SaveGameBtn->ViewRC = SaveGameBtn->ImgRC;
	SaveGameBtn->x = 950;
	SaveGameBtn->y = 480;

	Btn* CookieSelectBtn = new Btn();
	CookieSelectBtn->ID = eScene_CookieSelect;
	CookieSelectBtn->AssetFileName = TEXT("CookieSelect_btn.png");
	CookieSelectBtn->ImgRC = Rect(0, 0, 200, 165);
	CookieSelectBtn->ViewRC = CookieSelectBtn->ImgRC;
	CookieSelectBtn->x = 29;
	CookieSelectBtn->y = 475;

	Btn* NextChapterBtn = new Btn();
	NextChapterBtn->ID = eScene_Exit;
	NextChapterBtn->AssetFileName = TEXT("arrow_right.png");
	NextChapterBtn->ImgRC = Rect(0, 0, 100, 78);
	NextChapterBtn->ViewRC = NextChapterBtn->ImgRC;
	NextChapterBtn->x = 1310;
	NextChapterBtn->y = 275;

	Btn* PrevChapterBtn = new Btn();
	PrevChapterBtn->ID = eScene_Exit;
	PrevChapterBtn->AssetFileName = TEXT("arrow_left.png");
	PrevChapterBtn->ImgRC = Rect(0, 0, 100, 78);
	PrevChapterBtn->ViewRC = PrevChapterBtn->ImgRC;
	PrevChapterBtn->x = 10;
	PrevChapterBtn->y = 275;

	ChapterTitle = new StaticObject();
	ChapterTitle->Objtype = eObjectType_None;
	ChapterTitle->AssetFileName = TEXT("chapter_title.png");
	ChapterTitle->ImgRC = Rect(0, 0, 553, 120);
	ChapterTitle->ViewRC = ChapterTitle->ImgRC;
	ChapterTitle->x = 433;
	ChapterTitle->y = 8;
	
	Btn* StageClearedBtn = new Btn(0);
	StageClearedBtn->ID = eScene_Game;
	if (GameManager::GetInstance().stageClearList[0] == true)
	{
		StageClearedBtn->AssetFileName = TEXT("stage_cleared.png");
	}
	else
	{
		StageClearedBtn->AssetFileName = TEXT("stage_notyet.png");
	}
	StageClearedBtn->ImgRC = Rect(0, 0, 113, 112);
	StageClearedBtn->ViewRC = StageClearedBtn->ImgRC;
	StageClearedBtn->x = 148;
	StageClearedBtn->y = 273;

	Btn* StageNotYetBtn1 = new Btn(1);
	StageNotYetBtn1->ID = eScene_Game;
	if (GameManager::GetInstance().stageClearList[1] == true)
	{
		StageNotYetBtn1->AssetFileName = TEXT("stage_cleared.png");
	}
	else
	{
		StageNotYetBtn1->Enable = false;
		StageNotYetBtn1->AssetFileName = TEXT("stage_notyet.png");
	}
	StageNotYetBtn1->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn1->ViewRC = StageNotYetBtn1->ImgRC;
	StageNotYetBtn1->x = 347;
	StageNotYetBtn1->y = 273;

	Btn* StageNotYetBtn2 = new Btn(2);
	StageNotYetBtn2->ID = eScene_Game;
	if (GameManager::GetInstance().stageClearList[2] == true)
	{
		StageNotYetBtn2->AssetFileName = TEXT("stage_cleared.png");
	}
	else
	{
		StageNotYetBtn2->Enable = false;
		StageNotYetBtn2->AssetFileName = TEXT("stage_notyet.png");
	}
	StageNotYetBtn2->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn2->ViewRC = StageNotYetBtn2->ImgRC;
	StageNotYetBtn2->x = 535;
	StageNotYetBtn2->y = 183;

	Btn* StageNotYetBtn3 = new Btn(3);
	StageNotYetBtn3->ID = eScene_Game;
	if (GameManager::GetInstance().stageClearList[3] == true)
	{
		StageNotYetBtn3->AssetFileName = TEXT("stage_cleared.png");
	}
	else
	{
		StageNotYetBtn3->Enable = false;
		StageNotYetBtn3->AssetFileName = TEXT("stage_notyet.png");
	}
	StageNotYetBtn3->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn3->ViewRC = StageNotYetBtn3->ImgRC;
	StageNotYetBtn3->x = 535;
	StageNotYetBtn3->y = 368;

	Btn* StageNotYetBtn4 = new Btn();
	//StageNotYetBtn4->ID = eScene_Game;
	StageNotYetBtn4->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn4->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn4->ViewRC = StageNotYetBtn4->ImgRC;
	StageNotYetBtn4->x = 729;
	StageNotYetBtn4->y = 128;

	Btn* StageNotYetBtn5 = new Btn();
	//StageNotYetBtn5->ID = eScene_Game;
	StageNotYetBtn5->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn5->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn5->ViewRC = StageNotYetBtn5->ImgRC;
	StageNotYetBtn5->x = 729;
	StageNotYetBtn5->y = 424;

	Btn* StageNotYetBtn6 = new Btn();
	//StageNotYetBtn6->ID = eScene_Game;
	StageNotYetBtn6->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn6->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn6->ViewRC = StageNotYetBtn6->ImgRC;
	StageNotYetBtn6->x = 907;
	StageNotYetBtn6->y = 183;

	Btn* StageNotYetBtn7 = new Btn();
	//StageNotYetBtn7->ID = eScene_Game;
	StageNotYetBtn7->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn7->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn7->ViewRC = StageNotYetBtn7->ImgRC;
	StageNotYetBtn7->x = 907;
	StageNotYetBtn7->y = 368;

	Btn* StageNotYetBtn8 = new Btn();
	//StageNotYetBtn8->ID = eScene_Game;
	StageNotYetBtn8->AssetFileName = TEXT("stage_notyet.png");
	StageNotYetBtn8->ImgRC = Rect(0, 0, 113, 112);
	StageNotYetBtn8->ViewRC = StageNotYetBtn8->ImgRC;
	StageNotYetBtn8->x = 1094;
	StageNotYetBtn8->y = 273;


	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(GameStartBtn);
	infoStaticObj.emplace_back(CookieSelectBtn);
	infoStaticObj.emplace_back(NextChapterBtn);
	infoStaticObj.emplace_back(PrevChapterBtn);
	infoStaticObj.emplace_back(SaveGameBtn);
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

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->ImgRC = Rect(0, 0, 271, 279);
	popUp->ViewRC = popUp->ImgRC;
	popUp->Visible = false;
	infoStaticObj.emplace_back(popUp);
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