#pragma once
class XmlManager
{
public:
	static XmlManager& GetInstance();

	void ParsePlayerData(Player& player);

private:

};

