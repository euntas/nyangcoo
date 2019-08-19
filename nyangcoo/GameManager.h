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
	bool ChangeWave(); // true�� ����wave��, false�� ���� �Ұ�
	bool IsAllEnemyDead();
	bool IsGameEnd();
	bool IsWin; // true : �÷��̾� �¸� false : �� �¸�
	bool IsGrayScale;

	GameStage* curStage;
	int curWaveNum;
	int remainEnemyNum;
	vector<Character*> curEnemyList;
	vector<Character*> curCharacterList;
	Character* CommandPlayer;

	int btnID; // ��ư�� ������ �ִ� stageID�̴�. ��ư�� ������ ����ǰԲ� �Ǿ�����.

	// TODO. �������� Ŭ���� ���� ����. ���߿� DB�� �Űܾ� ��
	map<int, bool> stageClearList;

private:
};

