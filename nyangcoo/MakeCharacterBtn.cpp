#include "pch.h"
#include "MakeCharacterBtn.h"

MakeCharacterBtn::MakeCharacterBtn()
	: StaticObject(EObjectType::eObjectType_MakeCharacterBtn)
{

}

MakeCharacterBtn::MakeCharacterBtn(std::string characterName)
	: StaticObject(EObjectType::eObjectType_MakeCharacterBtn)
{
	IsReady = false;
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
	else if (characterName == "kiwi")
	{
		ID = eCharacter_kiwi;
	}
	else if (characterName == "windarcher")
	{
		ID = eCharacter_windarcher;
	}
	else {
		ID = eCharacter_pistachio;
	} 

	this->x = 50;
	this->y = 570;

	this->setImgRC(Gdiplus::Rect(0, 0, 85, 99));

	cost = 150;

	Character* tempChar = new Character();
	tempChar->CharacterXmlFileName = "Asset\\player\\player_" + NameStr + ".xml";
	XmlManager::GetInstance().ParseCharacterData(*tempChar);

	cost = tempChar->gold;

	std::string bgFilename = "slot\\bg_slot_" + std::to_string(cost) + ".png";

	makeSlotImg = new StaticObject();
	std::wstring tempFileName(bgFilename.begin(), bgFilename.end());
	makeSlotImg->setAssetFileName(tempFileName);

	std::string imgFilename = "slot\\slot_" + characterName + ".png";

	characterImg = new StaticObject();
	tempFileName = tempFileName.assign(imgFilename.begin(), imgFilename.end());
	characterImg->setAssetFileName(tempFileName);
	characterImg->setImgRC(Gdiplus::Rect(0, 0, 57, 64));
	characterImg->setViewRC(characterImg->getImgRC());
	characterImg->setX(12);
	characterImg->setY(13);
		
}

void MakeCharacterBtn::Init()
{

}

void MakeCharacterBtn::Update(float Delta)
{
	GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

	if (gs->gold >= cost) 
	{
		IsReady = true;
	}
	else
	{
		IsReady = false;
	}
}

void MakeCharacterBtn::Render(Gdiplus::Graphics* pGraphics)
{
	if (visible == false)
		return;

	// 배경
	if (makeSlotImg->getVisible() == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(makeSlotImg->getAssetFileName())).lock();

	GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

	if ((GameManager::GetInstance().IsGrayScale || IsReady == false) && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		Rect tempRC(x, y, imgRC.Width, imgRC.Height);
		pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, imgRC.Width, imgRC.Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		Rect tempRC(x, y, imgRC.Width, imgRC.Height);
		pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, imgRC.Width, imgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 캐릭터 그림
	if (characterImg->getVisible() == false)
		return;

	auto pImg2 = (AssetManager::GetInstance().GetImage(characterImg->getAssetFileName())).lock();
	
	Rect tempRC2(x + characterImg->getX(), y + characterImg->getY(), characterImg->getViewRC().Width, characterImg->getViewRC().Height);
	if ((GameManager::GetInstance().IsGrayScale || IsReady == false) && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		pGraphics->DrawImage(pImg2.get(), tempRC2, characterImg->getImgRC().X, characterImg->getImgRC().Y, characterImg->getImgRC().Width, characterImg->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg2.get(), tempRC2, characterImg->getImgRC().X, characterImg->getImgRC().Y, characterImg->getImgRC().Width, characterImg->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void MakeCharacterBtn::Release()
{

}

void MakeCharacterBtn::SendLButtonDown()
{
	// TODO. 골드가 cost 이상일때만 실행해야 함.
	GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

	if (gs->gold >= cost)
	{
		gs->gold -= cost;

		Character* c = MakeCharacter();
		SceneManager::GetInstance().GetCurScene()->addToInfoObj(c);
		GameManager::GetInstance().curCharacterList.emplace_back(c);

		Effect* ef = new Effect();
		ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
		XmlManager::GetInstance().ParseEffectData(*ef);
		ef->setX(c->getX());
		ef->setY(c->getY() - c->AniUnits[c->curState][0].Height / 2);
		ef->Init(new EffectGraphicsComponent(ef));

		SceneManager::GetInstance().GetCurScene()->addToInfoObj(ef);
	}
}

Character* MakeCharacterBtn::MakeCharacter()
{
	Character* resPlayer = new Character(eObjectType_Character);
	resPlayer->CharacterXmlFileName = "Asset\\player\\player_" + NameStr + ".xml";
	XmlManager::GetInstance().ParseCharacterData(*resPlayer);
	resPlayer->Init(new InputComponent(), new CharacterGraphicsComponent(resPlayer));

	resPlayer->atk += this->atk;
	resPlayer->hp += this->HP;

	return resPlayer;
}
