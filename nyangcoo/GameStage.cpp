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

	stageTitle = GameManager::GetInstance().StageTitle[_stageID];
}

int GameStage::getStageID()
{
	return stageID;
}

void GameStage::setStageID(int _stageID)
{
	stageID = _stageID;
}

wstring GameStage::getStageTitle()
{
	return stageTitle;
}

void GameStage::setStageTitle(wstring _stageTitle)
{
	stageTitle = _stageTitle;
}

int GameStage::getMaxGold()
{
	return maxGold;
}

void GameStage::setMaxGold(int _maxGold)
{
	maxGold = _maxGold;
}

int GameStage::getMaxHP()
{
	return maxHP;
}

void GameStage::setMaxHP(int _maxHP)
{
	maxHP = _maxHP;
}

int GameStage::getWaveNum()
{
	return waveNum;
}

void GameStage::setWaveNum(int _waveNum)
{
	waveNum = _waveNum;
}

vector<std::string>* GameStage::getEnemyNameList()
{
	return enemyNameList;
}

void GameStage::setEnemyNameList(vector<std::string>* _enemyNameList)
{
	for (int idx = 0; idx < MAX_WAVE_NUM; idx++)
	{
		enemyNameList[idx] = _enemyNameList[idx];
	}
}

std::string GameStage::getStageXmlFileName()
{
	return stageXmlFileName;
}

void GameStage::setStageXmlFileName(std::string _stageXmlfileName)
{
	stageXmlFileName = _stageXmlfileName;
}