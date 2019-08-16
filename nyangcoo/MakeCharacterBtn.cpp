#include "pch.h"
#include "MakeCharacterBtn.h"

MakeCharacterBtn::MakeCharacterBtn()
	: StaticObject(EObjectType::eObjectType_MakeCharacterBtn)
{

}

MakeCharacterBtn::MakeCharacterBtn(std::string characterName)
	: StaticObject(EObjectType::eObjectType_MakeCharacterBtn)
{
	CurStageID = 0;
	NameStr = characterName;

	if (characterName == "pistachio")
	{
		ID = eCharacter_pistachio;
	}
	else if (characterName == "whitechoco")
	{
		ID = eCharacter_whitechoco;
	}
	else if (characterName == "muscle")
	{
		ID = eCharacter_muscle;
	}
	else {
		ID = eCharacter_pistachio;
	} 

	this->x = 50;
	this->y = 575;

	this->ImgRC = Gdiplus::Rect(0, 0, 85, 99);

	cost = 150;

	std::string bgFilename = "slot\\bg_slot_" + std::to_string(cost) + ".png";

	makeSlotImg = new StaticObject();
	makeSlotImg->AssetFileName.assign(bgFilename.begin(), bgFilename.end());

	std::string imgFilename = "slot\\slot_" + characterName + ".png";

	characterImg = new StaticObject();
	characterImg->AssetFileName.assign(imgFilename.begin(), imgFilename.end());
	characterImg->ImgRC = Gdiplus::Rect(0, 0, 57, 64);
	characterImg->ViewRC = characterImg->ImgRC;
	characterImg->x = 12;
	characterImg->y = 13;
		
}

void MakeCharacterBtn::Init()
{

}

void MakeCharacterBtn::Update(float Delta)
{

}

void MakeCharacterBtn::Render(Gdiplus::Graphics* pGraphics)
{
	if (Visible == false)
		return;

	// ���
	if (makeSlotImg->Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(makeSlotImg->AssetFileName)).lock();

	Rect tempRC(x, y, ImgRC.Width, ImgRC.Height);
	pGraphics->DrawImage(pImg.get(), tempRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// ĳ���� �׸�
	if (characterImg->Visible == false)
		return;

	auto pImg2 = (AssetManager::GetInstance().GetImage(characterImg->AssetFileName)).lock();
	
	Rect tempRC2(x + characterImg->x, y + characterImg->y, characterImg->ViewRC.Width, characterImg->ViewRC.Height);
	pGraphics->DrawImage(pImg2.get(), tempRC2, characterImg->ImgRC.X, characterImg->ImgRC.Y, characterImg->ImgRC.Width, characterImg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}

void MakeCharacterBtn::Release()
{

}

void MakeCharacterBtn::SendLButtonDown()
{
	// TODO. ��尡 cost �̻��϶��� �����ؾ� ��.
	SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(MakeCharacter());
}

Character* MakeCharacterBtn::MakeCharacter()
{
	Character* resPlayer = new Character(eObjectType_Character);
	resPlayer->CharacterXmlFileName = "Asset\\player\\player_" + NameStr + ".xml";
	XmlManager::GetInstance().ParseCharacterData(*resPlayer);
	resPlayer->Init(new InputComponent(), new CharacterGraphicsComponent(resPlayer));

	resPlayer->atk += this->atk;

	return resPlayer;
}