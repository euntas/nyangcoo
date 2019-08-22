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
	void InitAllCharacterList();
	void InitStageSelectedList();

	bool IsWin; // true : �÷��̾� �¸� false : �� �¸�
	bool IsGrayScale;

	GameStage* curStage;
	
	int curWaveNum;
	int remainEnemyNum;
	vector<Character*> curEnemyList;
	vector<Character*> curCharacterList;
	Character* CommandPlayer;

	map<int, bool> slotList; // ���� ���� ����Ʈ, ���� ���� �ľ� ����
	map<std::string, bool> AllCharacterList; // ��ü ĳ������ �ر� ���� �ľ��� ���� 
	int coin; // ������

	int btnID; // ��ư�� ������ �ִ� stageID�̴�. ��ư�� ������ ����ǰԲ� �Ǿ�����.

	std::wstring StageTitle[4] = { L"���ѷα� ������ �Ʒ��� \n" , L"�������� �ι�° �Ʒ��� \n" , L"����° �������� �Ʒ��� \n" , L"���Ⱑ �������� ���� \n" };

	// TODO. �������� Ŭ���� ���� ����. ���߿� DB�� �Űܾ� ��
	map<int, bool> stageClearList; // <stageID, true or false>
	map<int, int> stageSelectedList; // ���ù� ����Ʈ. -1: ���þ���, 0: ù��° ���ù� ����, 1: �ι�° ���ù� ����

	int seletedSlotNum;

	int playerUpgradeLevel;

private:
};

