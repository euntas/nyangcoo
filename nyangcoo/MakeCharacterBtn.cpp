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

	this->ImgRC = Gdiplus::Rect(0, 0, 85, 99);

	cost = 150;

	Character* tempChar = new Character();
	tempChar->CharacterXmlFileName = "Asset\\player\\player_" + NameStr + ".xml";
	XmlManager::GetInstance().ParseCharacterData(*tempChar);

	cost = tempChar->gold;

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
	if (Visible == false)
		return;

	// 배경
	if (makeSlotImg->Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(makeSlotImg->AssetFileName)).lock();

	GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

	if ((GameManager::GetInstance().IsGrayScale || IsReady == false) && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
	{
		//gray scale conversion:
		Gdiplus::ColorMatrix matrix =
		{
			.3f, .3f, .3f,   0,   0,
			.6f, .6f, .6f,   0,   0,
			.1f, .1f, .1f,   0,   0,
			0,   0,   0,   1,   0,
			0,   0,   0,   0,   1
		};
		Gdiplus::ImageAttributes attr;
		attr.SetColorMatrix(&matrix,
			Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		Rect tempRC(x, y, ImgRC.Width, ImgRC.Height);
		pGraphics->DrawImage(pImg.get(), tempRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);
	}
	else
	{
		Rect tempRC(x, y, ImgRC.Width, ImgRC.Height);
		pGraphics->DrawImage(pImg.get(), tempRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 캐릭터 그림
	if (characterImg->Visible == false)
		return;

	auto pImg2 = (AssetManager::GetInstance().GetImage(characterImg->AssetFileName)).lock();
	
	Rect tempRC2(x + characterImg->x, y + characterImg->y, characterImg->ViewRC.Width, characterImg->ViewRC.Height);
	if ((GameManager::GetInstance().IsGrayScale || IsReady == false) && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
	{
		//gray scale conversion:
		Gdiplus::ColorMatrix matrix =
		{
			.3f, .3f, .3f,   0,   0,
			.6f, .6f, .6f,   0,   0,
			.1f, .1f, .1f,   0,   0,
			0,   0,   0,   1,   0,
			0,   0,   0,   0,   1
		};
		Gdiplus::ImageAttributes attr;
		attr.SetColorMatrix(&matrix,
			Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		pGraphics->DrawImage(pImg2.get(), tempRC2, characterImg->ImgRC.X, characterImg->ImgRC.Y, characterImg->ImgRC.Width, characterImg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg2.get(), tempRC2, characterImg->ImgRC.X, characterImg->ImgRC.Y, characterImg->ImgRC.Width, characterImg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
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
		//SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(MakeCharacter());

		Character* c = MakeCharacter();
		SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(c);
		GameManager::GetInstance().curCharacterList.emplace_back(c);

		// TODO. 지워야함 실험용 이펙트
		Effect* ef = new Effect();
		ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
		XmlManager::GetInstance().ParseEffectData(*ef);
		ef->setX(c->getX());
		ef->setY(c->getY() - c->AniUnits[c->curState][0].Height / 2);
		ef->Init(new EffectGraphicsComponent(ef));

		SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(ef);
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
