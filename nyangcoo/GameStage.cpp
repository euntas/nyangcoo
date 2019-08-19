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

	std::wstring ts[4] = { L"프롤로그 마녀의 훈련장 \n" , L"스테이지 두번째 훈련장 \n" , L"세번째 스테이지 훈련장 \n" , L"여기가 끝일지도 몰라 \n" };
	stageTitle = ts[_stageID];
}