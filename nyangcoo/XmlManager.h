#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParseCharacterData(Character& character);
	void ParseCharacterInitData(Character& character);
	void ParseEffectData(Effect& effect);
	void ParseStageData(GameStage& gameStage, int stageID);
	int getLastStageNum(int slotId);

	void ParseSavedData(); // 데이터를 읽어 GameManager에 저장한다.
	void LoadSlotData(int slotId);
	void SaveSlotData(int slotId);
	void DeleteSlotData(int slotId);

private:

};

