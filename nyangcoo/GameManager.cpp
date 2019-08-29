#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	
}

GameManager& GameManager::GetInstance()
{
	static GameManager gm;
	return gm;
}

void GameManager::InitCharacterSelectedList()
{
	characterSelectedList[0] = "pistachio";
	characterSelectedList[1] = "whitechoco";
	characterSelectedList[2] = "muscle";
	characterSelectedList[3] = "kiwi";
	characterSelectedList[4] = "windarcher";
}

void GameManager::Init(int stageID)
{
	ClearAll();
	
	coin = 0;

	playerUpgradeLevel = 0;

	for (int idx = 0; idx < ALL_STAGE_NUM; idx++)
	{
		if (idx == 0)
		{
			stageClearList.insert(make_pair(idx, true));
		}
		else
		{
			stageClearList.insert(make_pair(idx, false));
		}
		
		savedCoinList.insert(make_pair(idx, 0));
	}

	InitAllCharacterList();
	InitStageSelectedList();

	seletedSlotNum = -1;

	curStage = new GameStage(stageID);
	curWaveNum = 0;

	IsGrayScale = false;

	MakePlayer();
	MakeEnemyForWave(curWaveNum);
}

void GameManager::MakeEnemyForWave(int waveNum)
{
	curEnemyList.clear();

	int distCnt = 0;
	for (auto& it : curStage->getEnemyNameList()[waveNum])
	{
		Character* sampleEnemy = new Character(eObjectType_Enemy);
		sampleEnemy->CharacterXmlFileName = "Asset\\player\\player_" + it + ".xml";
		XmlManager::GetInstance().ParseCharacterData(*sampleEnemy);
		sampleEnemy->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy));
		sampleEnemy->setX(sampleEnemy->getX() + distCnt * 200);
		if (it == "titan" || it == "macho" || it =="knight" || it == "redknight"
			|| it == "tank" || it == "redtank")
			sampleEnemy->setBleft(true);

		curEnemyList.emplace_back(sampleEnemy);

		distCnt++;
	}
}

void GameManager::MakePlayer()
{
	CommandPlayer = new Character(eObjectType_Player);
	CommandPlayer->CharacterXmlFileName = "Asset\\player\\player_moonlight.xml";
	XmlManager::GetInstance().ParseCharacterData(*CommandPlayer);
	CommandPlayer->Init(new InputComponent(), new CharacterGraphicsComponent(CommandPlayer));

	remainEnemyNum = curEnemyList.size();
}

void GameManager::ClearAll()
{
	curStage = nullptr;
	CommandPlayer = nullptr;
	curWaveNum = 0;
	curEnemyList.clear();
	curCharacterList.clear();
	stageClearList.clear();
	stageSelectedList.clear();
	AllCharacterList.clear();
}

bool GameManager::ChangeWave()
{
	if (curWaveNum + 1 >= curStage->getWaveNum())
	{
		return false;
	}

	curWaveNum++;

	MakeEnemyForWave(curWaveNum);

	return true;
}

bool GameManager::IsAllEnemyDead()
{
	bool res = true;
	int remainCnt = 0;

	for (auto& it : curEnemyList)
	{
		if (it->getEnable() == true)
		{
			remainCnt++;
			res = false;
		}
	}

	remainEnemyNum = remainCnt;

	return res;
}

bool GameManager::IsGameEnd()
{
	// 플레이어 상태 확인
	if (CommandPlayer->hp <= 0)
	{
		IsWin = false;
		return true;
	}

	// 적들 상태 확인
	if (curWaveNum + 1 < curStage->getWaveNum())
		return false;

	for (auto& it : curEnemyList)
	{
		if (it == nullptr)
			continue;

		if (it->getEnable() == true || it->getVisible() == true)
		{
			return false;
		}
	}

	IsWin = true;
	return true;
}

void GameManager::InitAllCharacterList()
{
	std::string initNameList[] = { "brave" , "kiwi" , "lemon" , "macho" , "moonlight" , "moonrabit" , "muscle" , "pistachio" , "plum" , "titan" , "whitechoco" , "windarcher" };
	
	for (int idx = 0; idx < initNameList->size(); idx++)
	{
		AllCharacterList.insert(make_pair(initNameList[idx], true));
	}
}

void GameManager::InitStageSelectedList()
{
	for (int i = 0; i < ALL_STAGE_NUM; i++)
	{
		stageSelectedList.insert(make_pair(i, -1));
	}
}