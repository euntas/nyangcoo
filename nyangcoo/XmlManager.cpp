#include "pch.h"
#include "XmlManager.h"

XmlManager& XmlManager::GetInstance()
{
	static XmlManager mgr;
	return mgr;
}

int XmlManager::GetCharacterCost(std::string name)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();

	std::string filename = "Asset\\player\\player_ " + name + ".xml";
	doc->LoadFile(filename.c_str());

	XMLElement* Root = doc->RootElement();

	int gold = 0;
	gold = atoi(Root->Attribute("gold"));

	return gold;
}

void XmlManager::ParseCharacterData(Character& character)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(character.CharacterXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	character.name = name;
	character.speed = speed;
	character.atk = atk;
	character.atkSpeed = atkSpeed;
	character.atkDist = atkDist;
	character.hp = hp;
	character.maxHp = hp;
	character.gold = gold;

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
		float height = atof(SpriteNode->Attribute("h"));

		character.CharacterAssetFileName[state] = imagePath;
		character.frameNum[state] = frameNum;
		character.frameDelta[state] = delta;
		character.spriteRowNum[state] = rowNum;
		character.imgNumPerLine[state] = imgNumPerLine;
		character.frameWidth[state] = width;
		character.frameHeight[state] = height;
	}
}

void XmlManager::ParseCharacterInitData(Character& character)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(character.CharacterXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();

	std::string name = Root->Attribute("name");
	float speed = atoi(Root->Attribute("speed"));
	int atk = atoi(Root->Attribute("atk"));
	float atkSpeed = atoi(Root->Attribute("atkSpeed"));
	float atkDist = atoi(Root->Attribute("atkDist"));
	int hp = atoi(Root->Attribute("hp"));
	int gold = atoi(Root->Attribute("gold"));

	character.name = name;
	character.speed = speed;
	character.atk = atk;
	character.atkSpeed = atkSpeed;
	character.atkDist = atkDist;
	character.hp = hp;
	character.maxHp = hp;
	character.gold = gold;
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
		float height = atof(SpriteNode->Attribute("h"));

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

void XmlManager::ParseStageData(GameStage& gameStage, int stageID)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(gameStage.stageXmlFileName.c_str());

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("Stage"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("Stage"))
	{
		int tempID = atoi(Node->Attribute("stageID"));

		if (stageID != tempID)
			continue;

		gameStage.stageID = tempID;

		gameStage.maxGold = atoi(Node->Attribute("maxGold"));
		gameStage.maxHP = atoi(Node->Attribute("maxHP"));
		gameStage.waveNum = atoi(Node->Attribute("waveNum"));

		std::string imagePathTemp = Node->Attribute("imagePath");
		std::wstring imagePath;
		imagePath.assign(imagePathTemp.begin(), imagePathTemp.end());
		gameStage.bg->AssetFileName = imagePath;

		XMLElement* ImgRCNode = Node->FirstChildElement("ImgRC");
		gameStage.bg->ImgRC.X = atoi(ImgRCNode->Attribute("x"));
		gameStage.bg->ImgRC.Y = atoi(ImgRCNode->Attribute("y"));
		gameStage.bg->ImgRC.Width = atoi(ImgRCNode->Attribute("width"));
		gameStage.bg->ImgRC.Height = atoi(ImgRCNode->Attribute("height"));

		XMLElement* ViewRCNode = Node->FirstChildElement("ViewRC");
		gameStage.bg->ViewRC.X = atoi(ViewRCNode->Attribute("x"));
		gameStage.bg->ViewRC.Y = atoi(ViewRCNode->Attribute("y"));
		gameStage.bg->ViewRC.Width = atoi(ViewRCNode->Attribute("width"));
		gameStage.bg->ViewRC.Height = atoi(ViewRCNode->Attribute("height"));

		XMLElement* EnemyNode;
		for (EnemyNode = (tinyxml2::XMLElement*)Node->FirstChildElement("enemyList"); EnemyNode != 0; EnemyNode = (tinyxml2::XMLElement*)EnemyNode->NextSiblingElement("enemyList"))
		{
			int tempwavecnt = atoi(EnemyNode->Attribute("wave"));

			XMLElement* NameNode;
			for (NameNode = (tinyxml2::XMLElement*)EnemyNode->FirstChildElement("name"); NameNode != 0; NameNode = (tinyxml2::XMLElement*)NameNode->NextSiblingElement("name"))
			{
				gameStage.enemyNameList[tempwavecnt].emplace_back(NameNode->GetText());
			}
		}
	}
}

void XmlManager::ParseSavedData()
{
	std::string filename = "Asset\\stage\\save_info.xml";

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(filename.c_str());

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("slot"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("slot"))
	{
		int slotNum = atoi(Node->Attribute("slotNum"));
		bool state = Node->BoolAttribute("state");
		int coin = atoi(Node->Attribute("coin"));

		GameManager::GetInstance().slotList[slotNum] = state;
		GameManager::GetInstance().savedCoinList[slotNum] = coin;
	}
}

int XmlManager::getLastStageNum(int slotId)
{
	std::string filename = "Asset\\stage\\save_info.xml";

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(filename.c_str());

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("slot"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("slot"))
	{
		int slotNum = atoi(Node->Attribute("slotNum"));
		bool state = Node->BoolAttribute("state");

		if (slotNum == slotId)
		{
			XMLElement* stageNode;
			int lastStage = 0;
			for (stageNode = (tinyxml2::XMLElement*)Node->FirstChildElement("stage"); stageNode != 0; stageNode = (tinyxml2::XMLElement*)stageNode->NextSiblingElement("stage"))
			{
				if (stageNode->BoolAttribute("state") == true)
				{
					lastStage++;
				}
				else
				{
					if (lastStage != 0)
					{
						lastStage--;
						break;
					}
				}
			}

			return lastStage;
		}
	}
}

void XmlManager::LoadSlotData(int slotId)
{
	std::string filename = "Asset\\stage\\save_info.xml";

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(filename.c_str());

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("slot"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("slot"))
	{
		int slotNum = atoi(Node->Attribute("slotNum"));
		bool slotState = Node->BoolAttribute("state");
		int coin = atoi(Node->Attribute("coin"));

		GameManager::GetInstance().coin = coin;

		if (slotNum == slotId && slotState == true)
		{
			XMLElement* stageNode;
			for (stageNode = (tinyxml2::XMLElement*)Node->FirstChildElement("stage"); stageNode != 0; stageNode = (tinyxml2::XMLElement*)stageNode->NextSiblingElement("stage"))
			{
				int stageId = atoi(stageNode->Attribute("stageId"));
				bool state = stageNode->BoolAttribute("state");
				int selectedStr = atoi(stageNode->Attribute("selectedStr"));

				GameManager::GetInstance().stageClearList[stageId] = state;
				GameManager::GetInstance().stageSelectedList[stageId] = selectedStr;
			}

			XMLElement* characterNode;
			for (characterNode = (tinyxml2::XMLElement*)Node->FirstChildElement("character"); characterNode != 0; characterNode = (tinyxml2::XMLElement*)characterNode->NextSiblingElement("character"))
			{
				bool state = characterNode->BoolAttribute("state");
				
				GameManager::GetInstance().AllCharacterList[characterNode->GetText()] = state;
			}
		}
		else
		{
			printf("로드에 실패했습니다. \n");
		}
	}
}

void XmlManager::SaveSlotData(int slotId)
{
	std::string filename = "Asset\\stage\\save_info.xml";

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(filename.c_str());

	if (!doc)
		return;

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("slot"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("slot"))
	{
		int slotNum = atoi(Node->Attribute("slotNum"));

		if (slotNum == slotId)
		{
			Node->SetAttribute("state", true);

			int coin = GameManager::GetInstance().coin;
			Node->SetAttribute("coin", coin);

			XMLElement* stageNode;
			for (stageNode = (tinyxml2::XMLElement*)Node->FirstChildElement("stage"); stageNode != 0; stageNode = (tinyxml2::XMLElement*)stageNode->NextSiblingElement("stage"))
			{
				int stageId = atoi(stageNode->Attribute("stageId"));

				bool stageClear = GameManager::GetInstance().stageClearList[stageId];
				int stageSelected = GameManager::GetInstance().stageSelectedList[stageId];

				stageNode->SetAttribute("state", stageClear);
				stageNode->SetAttribute("selectedStr", stageSelected);
			}

			XMLElement* characterNode;
			for (characterNode = (tinyxml2::XMLElement*)Node->FirstChildElement("character"); characterNode != 0; characterNode = (tinyxml2::XMLElement*)characterNode->NextSiblingElement("character"))
			{
				bool character = GameManager::GetInstance().AllCharacterList[characterNode->GetText()];
				characterNode->SetAttribute("state", character);
			}
		}
	}

	doc->SaveFile(filename.c_str());
}

void XmlManager::DeleteSlotData(int slotId)
{
	std::string filename = "Asset\\stage\\save_info.xml";

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(filename.c_str());

	if (!doc)
		return;

	XMLElement* Root = doc->RootElement();
	XMLElement* Node;

	for (Node = (tinyxml2::XMLElement*)Root->FirstChildElement("slot"); Node != 0; Node = (tinyxml2::XMLElement*)Node->NextSiblingElement("slot"))
	{
		int slotNum = atoi(Node->Attribute("slotNum"));
		
		if (slotNum == slotId)
		{
			Node->SetAttribute("state", false);
			Node->SetAttribute("coin", 0);

			XMLElement* stageNode;
			for (stageNode = (tinyxml2::XMLElement*)Node->FirstChildElement("stage"); stageNode != 0; stageNode = (tinyxml2::XMLElement*)stageNode->NextSiblingElement("stage"))
			{
				int stageId = atoi(stageNode->Attribute("stageId"));

				stageNode->SetAttribute("state", false);
				stageNode->SetAttribute("selectedStr", -1);
			}

			XMLElement* characterNode;
			for (characterNode = (tinyxml2::XMLElement*)Node->FirstChildElement("character"); characterNode != 0; characterNode = (tinyxml2::XMLElement*)characterNode->NextSiblingElement("character"))
			{
				characterNode->SetAttribute("state", false);
			}
		}
	}

	doc->SaveFile(filename.c_str());
}



