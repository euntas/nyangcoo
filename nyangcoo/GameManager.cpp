#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	// TODO. ���߿� DB�� �Űܾ� ��
	stageClearList.insert(make_pair(0, true));
	stageClearList.insert(make_pair(1, false));
	stageClearList.insert(make_pair(2, false));
	stageClearList.insert(make_pair(3, false));
}

GameManager& GameManager::GetInstance()
{
	static GameManager gm;
	return gm;
}

void GameManager::Init(int stageID)
{
	ClearAll();

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
		if (it == "titan" || it == "macho")
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
	// �÷��̾� ���� Ȯ��
	if (CommandPlayer->hp <= 0)
	{
		IsWin = false;
		return true;
	}

	// ���� ���� Ȯ��
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
