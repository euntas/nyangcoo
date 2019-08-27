#pragma once
class GameStage
{
public:
	GameStage();
	GameStage(int _stageID);

	void Init(int _stageID);

	// TODO. bg�� ������ �ø���
	StaticObject* bg;

	// Getter, Setter
	int getStageID();
	void setStageID(int _stageID);

	wstring getStageTitle();
	void setStageTitle(wstring _stageTitle);

	int getMaxGold();
	void setMaxGold(int _maxGold);

	int getMaxHP();
	void setMaxHP(int _maxHP);

	int getWaveNum();
	void setWaveNum(int _waveNum);

	vector<std::string>* getEnemyNameList();
	void setEnemyNameList(vector<std::string>* _enemyNameList);

	std::string getStageXmlFileName();
	void setStageXmlFileName(std::string _stageXmlfileName);

private:
	int stageID;
	int maxGold;
	int maxHP;
	wstring stageTitle;
	
	int waveNum; // �� ���������� wave ����

	vector<std::string> enemyNameList[MAX_WAVE_NUM];

	std::string stageXmlFileName;
};

