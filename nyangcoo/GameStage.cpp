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
	stageXmlFileName = "Asset\\stage\\stage_info.xml";
	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	XmlManager::GetInstance().ParseStageData(*this, _stageID);

	stageTitle = L"���ѷα� ������ �Ʒ��� \n";
}