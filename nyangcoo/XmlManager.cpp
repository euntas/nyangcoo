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




