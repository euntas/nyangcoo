#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParsePlayerData(Player& player);
	void ParsePlayerInitData(Player& player);
	void ParseEnemyData(Enemy& enemy);
	void ParseEnemyInitData(Enemy& enemy);
	void ParseEffectData(Effect& effect);

private:

};

