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
	void InitAllCharacterList();
	void InitStageSelectedList();

	bool IsWin; // true : 플레이어 승리 false : 적 승리
	bool IsGrayScale;

	GameStage* curStage;
	
	int curWaveNum;
	int remainEnemyNum;
	vector<Character*> curEnemyList;
	vector<Character*> curCharacterList;
	Character* CommandPlayer;

	map<int, bool> slotList; // 저장 슬롯 리스트, 저장 상태 파악 위해
	map<std::string, bool> AllCharacterList; // 전체 캐릭터의 해금 상태 파악을 위해 
	int coin; // 냥코인

	int btnID; // 버튼이 가지고 있는 stageID이다. 버튼이 눌리면 저장되게끔 되어있음.

	std::wstring StageTitle[4] = { L"프롤로그 마녀의 훈련장 \n" , L"스테이지 두번째 훈련장 \n" , L"세번째 스테이지 훈련장 \n" , L"여기가 끝일지도 몰라 \n" };

	// TODO. 스테이지 클리어 정보 관련. 나중에 DB로 옮겨야 함
	map<int, bool> stageClearList; // <stageID, true or false>
	map<int, int> stageSelectedList; // 선택문 리스트. -1: 선택안함, 0: 첫번째 선택문 선택, 1: 두번째 선택문 선택

	int seletedSlotNum;

	int playerUpgradeLevel;

private:
};

