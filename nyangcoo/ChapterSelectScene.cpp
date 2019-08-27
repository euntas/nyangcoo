#include "pch.h"
#include "ChapterSelectScene.h"

ChapterSelectScene::ChapterSelectScene() : Scene()
{
	name = "Scene_ChapterSelect";

	Init();
}

void ChapterSelectScene::Init()
{
	infoStaticObj.clear();

	bg = new StaticObject();
	bg->setObjtype(eObjectType_BGImage);
	bg->setAssetFileName(TEXT("ChapterSelect_bg.png"));
	bg->setImgRC(Rect(0, 0, 1420, 672));
	bg->setViewRC(bg->getImgRC());

	infoStaticObj.emplace_back(bg);

	Btn* GameStartBtn = new Btn(eScene_Start, TEXT("BackMain_btn.png"), Rect(0, 0, 200, 173), Rect(0, 0, 200, 173), 1187, 466);
	infoStaticObj.emplace_back(GameStartBtn);

	Btn* SaveGameBtn = new Btn(eSaveLoadBtn_Save, TEXT("saveload\\SaveGame_btn.png"), Rect(0, 0, 200, 158), Rect(0, 0, 200, 158), 950, 480);
	infoStaticObj.emplace_back(SaveGameBtn);

	Btn* CookieSelectBtn = new Btn(eScene_CookieSelect, TEXT("CookieSelect_btn.png"), Rect(0, 0, 200, 165), Rect(0, 0, 200, 165), 29, 475);
	infoStaticObj.emplace_back(CookieSelectBtn);

	ChapterTitle = new StaticObject();
	ChapterTitle->setObjtype(eObjectType_None);
	ChapterTitle->setAssetFileName(TEXT("chapter_title.png"));
	ChapterTitle->setImgRC(Rect(0, 0, 553, 120));
	ChapterTitle->setViewRC(ChapterTitle->getImgRC());
	ChapterTitle->setX(433);
	ChapterTitle->setY(8);
	infoStaticObj.emplace_back(ChapterTitle);
	
	Btn* StageClearedBtn = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 148, 273, 0);
	if (GameManager::GetInstance().stageClearList[0] == true)
	{
		StageClearedBtn->setAssetFileName(TEXT("stage_cleared_0.png"));
	}
	infoStaticObj.emplace_back(StageClearedBtn);

	Btn* StageNotYetBtn1 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 347, 273, 1);
	if (GameManager::GetInstance().stageClearList[1] == true)
	{
		StageNotYetBtn1->setAssetFileName(TEXT("stage_cleared_1.png"));
	}
	infoStaticObj.emplace_back(StageNotYetBtn1);

	Btn* StageNotYetBtn2 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 535, 183, 2);
	if (GameManager::GetInstance().stageClearList[2] == true)
	{
		StageNotYetBtn2->setAssetFileName(TEXT("stage_cleared_2.png"));
	}
	else
	{
		StageNotYetBtn2->setEnable(false);
	}
	infoStaticObj.emplace_back(StageNotYetBtn2);

	Btn* StageNotYetBtn3 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 535, 368, 3);
	if (GameManager::GetInstance().stageClearList[3] == true)
	{
		StageNotYetBtn3->setAssetFileName(TEXT("stage_cleared.png"));
	}
	else
	{
		StageNotYetBtn3->setEnable(false);
	}
	infoStaticObj.emplace_back(StageNotYetBtn3);

	Btn* StageNotYetBtn4 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 729, 128);
	infoStaticObj.emplace_back(StageNotYetBtn4);

	Btn* StageNotYetBtn5 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 729, 424);
	infoStaticObj.emplace_back(StageNotYetBtn5);

	Btn* StageNotYetBtn6 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 907, 183);
	infoStaticObj.emplace_back(StageNotYetBtn6);

	Btn* StageNotYetBtn7 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 907, 368);
	infoStaticObj.emplace_back(StageNotYetBtn7);

	Btn* StageNotYetBtn8 = new Btn(eScene_Game, TEXT("stage_notyet.png"), Rect(0, 0, 113, 112), Rect(0, 0, 113, 112), 1094, 273);
	infoStaticObj.emplace_back(StageNotYetBtn8);

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());
	popUp->setVisible(false);
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