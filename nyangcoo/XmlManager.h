#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParseCharacterData(Character& character);
	void ParseCharacterInitData(Character& character);
	void ParseEffectData(Effect& effect);
	void ParseStageData(GameStage& gameStage, int stageID);

private:

};

