#pragma once
class GameManager
{
public:
	GameManager();
	static GameManager& GetInstance();

	void Init(int stageID);

	void ClearAll();
	void MakePlayer();
	void MakeEnemyForWave(int waveNum);
	bool ChangeWave(); // true면 다음wave로, false면 변경 불가
	bool IsAllEnemyDead();
	bool IsGameEnd();
	bool IsWin; // true : 플레이어 승리 false : 적 승리
	bool IsGrayScale;

	GameStage* curStage;
	int curWaveNum;
	int remainEnemyNum;
	vector<Character*> curEnemyList;
	vector<Character*> curCharacterList;
	Character* CommandPlayer;

private:
};

