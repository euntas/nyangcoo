#include "pch.h"
#include "XmlManager.h"

XmlManager& XmlManager::GetInstance()
{
	static XmlManager mgr;
	return mgr;
}

void XmlManager::ParsePlayerData(Player& player)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(player.PlayerXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	player.name = name;
	player.speed = speed;
	player.atk = atk;
	player.atkSpeed = atkSpeed;
	player.atkDist = atkDist;
	player.hp = hp;
	player.gold = gold;

	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("TextureAtlas"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("TextureAtlas"))
	{
		std::string imagePathTemp = Node->Attribute("imagePath");
		imagePathTemp.replace(imagePathTemp.find('\\'), 1, "");
		std::wstring imagePath;
		imagePath.assign(imagePathTemp.begin(), imagePathTemp.end());

		int state = atoi(Node->Attribute("state"));

		int frameNum = atoi(Node->Attribute("frameNum"));
		int rowNum = atoi(Node->Attribute("rowNum"));
		float delta = atof(Node->Attribute("delta"));
		int imgNumPerLine = atoi(Node->Attribute("imgNumPerLine"));

		XMLElement* SpriteNode = Node->FirstChildElement("sprite");

		float width = atof(SpriteNode->Attribute("w"));
		float height = atof(SpriteNode->Attribute("w"));

		player.PlayerAssetFileName[state] = imagePath;
		player.frameNum[state] = frameNum;
		player.frameDelta[state] = delta;
		player.spriteRowNum[state] = rowNum;
		player.imgNumPerLine[state] = imgNumPerLine;
		player.frameWidth[state] = width;
		player.frameHeight[state] = height;
	}
}

void XmlManager::ParsePlayerInitData(Player& player)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(player.PlayerXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	player.name = name;
	player.speed = speed;
	player.atk = atk;
	player.atkSpeed = atkSpeed;
	player.atkDist = atkDist;
	player.hp = hp;
	player.gold = gold;
}

void XmlManager::ParseEnemyData(Enemy& enemy)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(enemy.EnemyXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	enemy.name = name;
	enemy.speed = speed;
	enemy.atk = atk;
	enemy.atkSpeed = atkSpeed;
	enemy.atkDist = atkDist;
	enemy.hp = hp;
	enemy.gold = gold;

	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("TextureAtlas"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("TextureAtlas"))
	{
		std::string imagePathTemp = Node->Attribute("imagePath");
		imagePathTemp.replace(imagePathTemp.find('\\'), 1, "");
		std::wstring imagePath;
		imagePath.assign(imagePathTemp.begin(), imagePathTemp.end());

		int state = atoi(Node->Attribute("state"));

		int frameNum = atoi(Node->Attribute("frameNum"));
		int rowNum = atoi(Node->Attribute("rowNum"));
		float delta = atof(Node->Attribute("delta"));
		int imgNumPerLine = atoi(Node->Attribute("imgNumPerLine"));

		XMLElement* SpriteNode = Node->FirstChildElement("sprite");

		float width = atof(SpriteNode->Attribute("w"));
		float height = atof(SpriteNode->Attribute("w"));

		enemy.EnemyAssetFileName[state] = imagePath;
		enemy.frameNum[state] = frameNum;
		enemy.frameDelta[state] = delta;
		enemy.spriteRowNum[state] = rowNum;
		enemy.imgNumPerLine[state] = imgNumPerLine;
		enemy.frameWidth[state] = width;
		enemy.frameHeight[state] = height;
	}
}

void XmlManager::ParseEnemyInitData(Enemy& enemy)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(enemy.EnemyXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	enemy.name = name;
	enemy.speed = speed;
	enemy.atk = atk;
	enemy.atkSpeed = atkSpeed;
	enemy.atkDist = atkDist;
	enemy.hp = hp;
	enemy.gold = gold;
}

void XmlManager::ParseEffectData(Effect& effect)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(effect.EffectXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("TextureAtlas"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("TextureAtlas"))
	{
		std::string imagePathTemp = Node->Attribute("imagePath");
		imagePathTemp.replace(imagePathTemp.find('\\'), 1, "");
		std::wstring imagePath;
		imagePath.assign(imagePathTemp.begin(), imagePathTemp.end());

		int effectId = atoi(Node->Attribute("effectId"));

		int frameNum = atoi(Node->Attribute("frameNum"));
		int rowNum = atoi(Node->Attribute("rowNum"));
		float delta = atof(Node->Attribute("delta"));
		int imgNumPerLine = atoi(Node->Attribute("imgNumPerLine"));

		XMLElement* SpriteNode = Node->FirstChildElement("sprite");

		float width = atof(SpriteNode->Attribute("w"));
		float height = atof(SpriteNode->Attribute("w"));

		effect.EffectId = effectId;
		effect.AssetFileName = imagePath;
		effect.frameNum = frameNum;
		effect.frameDelta = delta;
		effect.spriteRowNum = rowNum;
		effect.imgNumPerLine = imgNumPerLine;
		effect.frameWidth = width;
		effect.frameHeight = height;
	}
}




