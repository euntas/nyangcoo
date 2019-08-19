#pragma once
class GameStage
{
public:
	GameStage();
	GameStage(int _stageID);

	void Init(int _stageID);

	int stageID;
	wstring stageTitle;
	int maxGold;
	int maxHP;
	StaticObject* bg;
	int waveNum; // �� ���������� wave ����
	
	vector<std::string> enemyNameList[MAX_WAVE_NUM];

	std::string stageXmlFileName;
};

