#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParseCharacterData(Character& character);
	void ParseCharacterInitData(Character& character);
	void ParseEnemyData(Enemy& enemy);
	void ParseEnemyInitData(Enemy& enemy);
	void ParseEffectData(Effect& effect);

private:

};

