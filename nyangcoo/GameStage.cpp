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

	std::wstring ts[4] = { L"���ѷα� ������ �Ʒ��� \n" , L"�������� �ι�° �Ʒ��� \n" , L"����° �������� �Ʒ��� \n" , L"���Ⱑ �������� ���� \n" };
	stageTitle = ts[_stageID];
}