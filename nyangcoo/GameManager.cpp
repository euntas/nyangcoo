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

void GameManager::Init(int stageID)
{
	ClearAll();
	
	coin = 0;

	// TODO. 나중에 DB로 옮겨야 함
	stageClearList.insert(make_pair(0, true));
	stageClearList.insert(make_pair(1, false));
	stageClearList.insert(make_pair(2, false));
	stageClearList.insert(make_pair(3, false));

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
	for (auto& it : curStage->enemyNameList[waveNum])
	{
		Character* sampleEnemy = new Character(eObjectType_Enemy);
		sampleEnemy->CharacterXmlFileName = "Asset\\player\\player_" + it + ".xml";
		XmlManager::GetInstance().ParseCharacterData(*sampleEnemy);
		sampleEnemy->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy));
		sampleEnemy->x += (distCnt * 200);
		if (it == "titan" || it == "macho" || it =="knight" || it == "redknight"
			|| it == "tank" || it == "redtank")
			sampleEnemy->bleft = true;

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
	if (curWaveNum + 1 >= curStage->waveNum)
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
		if (it->Enable == true)
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
	if (curWaveNum + 1 < curStage->waveNum)
		return false;

	for (auto& it : curEnemyList)
	{
		if (it == nullptr)
			continue;

		if (it->Enable == true || it->Visible == true)
		{
			return false;
		}
	}

	IsWin = true;
	return true;
}

void GameManager::InitAllCharacterList()
{
	AllCharacterList.insert(make_pair("brave", true));
	AllCharacterList.insert(make_pair("kiwi", true));
	AllCharacterList.insert(make_pair("lemon", true));
	AllCharacterList.insert(make_pair("macho", true));
	AllCharacterList.insert(make_pair("moonlight", true));
	AllCharacterList.insert(make_pair("moonrabit", true));
	AllCharacterList.insert(make_pair("muscle", true));
	AllCharacterList.insert(make_pair("pistachio", true));
	AllCharacterList.insert(make_pair("plum", true));
	AllCharacterList.insert(make_pair("titan", true));
	AllCharacterList.insert(make_pair("whitechoco", true));
	AllCharacterList.insert(make_pair("windarcher", true));
}

void GameManager::InitStageSelectedList()
{
	for (int i = 0; i < 4; i++)
	{
		stageSelectedList.insert(make_pair(i, -1));
	}
}