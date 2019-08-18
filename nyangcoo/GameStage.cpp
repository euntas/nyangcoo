#include "pch.h"
#include "GameStage.h"

GameStage::GameStage()
{
	Init(0);
}

GameStage::GameStage(int _stageID)
{
	Init(_stageID);
}

void GameStage::Init(int _stageID)
{
	stageID = _stageID;

	stageTitle = L"ÇÁ·Ñ·Î±× ¸¶³àÀÇ ÈÆ·ÃÀå \n";

	maxGold = 1500;
	maxHP = 1000;

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg_bamboo2.png");
	bg->ImgRC = Rect(0, 0, 2840, 672);
	bg->ViewRC = Rect(0, 0, 1420, 672);

	//waveNum = 3;
	waveNum = 1;

	enemyNameList[0] = {"muscle", "titan", "titan"};
	//enemyNameList[1] = {"titan" , "muscle", "titan", "titan" };
	//enemyNameList[2] = { "muscle", "titan", "titan" };
}