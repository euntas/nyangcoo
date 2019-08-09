#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParsePlayerData(Player& player);
	void ParseEffectData(Effect& effect);

private:

};

