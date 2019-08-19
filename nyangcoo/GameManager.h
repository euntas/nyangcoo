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

	int btnID; // 버튼이 가지고 있는 stageID이다. 버튼이 눌리면 저장되게끔 되어있음.

	// TODO. 스테이지 클리어 정보 관련. 나중에 DB로 옮겨야 함
	map<int, bool> stageClearList;

private:
};

