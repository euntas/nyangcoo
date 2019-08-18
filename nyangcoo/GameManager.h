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
	void ChangeWave();
	bool IsAllEnemyDead();
	bool IsGameEnd();
	bool IsWin; // true : ÇÃ·¹ÀÌ¾î ½Â¸® false : Àû ½Â¸®


	GameStage* curStage;
	int curWaveNum;
	int remainEnemyNum;
	vector<Character*> curEnemyList;
	vector<Character*> curCharacterList;
	Character* CommandPlayer;

private:
};

