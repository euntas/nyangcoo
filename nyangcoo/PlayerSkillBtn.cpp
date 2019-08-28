#include "pch.h"
#include "PlayerSkillBtn.h"

PlayerSkillBtn::PlayerSkillBtn()
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{

}

PlayerSkillBtn::PlayerSkillBtn(std::string skillName)
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{
	enable = false;

	Name = skillName;

	Init();
}

void PlayerSkillBtn::Init()
{
	angle = 0.f;

	std::string imgFilename;

	imgFilename = "skill_" + Name + ".png";

	if (Name == "heal")
	{
		skillType = eSkill_Heal;
	}
	else if (Name == "blizzard")
	{
		skillType = eSkill_Blizzard;
	}
	else if (Name == "beam")
	{
		skillType = eSkill_Razer;
	}

	btnImg = new StaticObject();
	btnImg->setAssetFileName(btnImg->getAssetFileName().assign(imgFilename.begin(), imgFilename.end()));
	btnImg->setImgRC(Gdiplus::Rect(0, 0, 127, 144));
	btnImg->setViewRC(btnImg->getImgRC());
}

void PlayerSkillBtn::Update(float Delta)
{
	if (enable == false)
	{
		if (Name == "heal")
		{
			angle += 1;
		}
		else if (Name == "blizzard")
		{
			angle += 0.5;
		}
		else if (Name == "razer")
		{
			//angle += 0.25;
			angle += 3;
		}
	}

	if (angle >= 360)
	{
		angle = 0;
		enable = true;
	}
}

void PlayerSkillBtn::Render(Gdiplus::Graphics* pGraphics)
{
	btnImg->Render(pGraphics);

	// 쿨타임 관련
	Gdiplus::SolidBrush gray(Color(128, 0, 0, 0));
	Gdiplus::SolidBrush empty(Color(0, 0, 0, 0));

	if (enable == false)
	{
		Rect coverImg(0, 0, btnImg->getImgRC().Width, btnImg->getImgRC().Height);
		Gdiplus::Bitmap bitmap2(coverImg.Width, coverImg.Height, PixelFormat32bppARGB);
		Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(&bitmap2);

		auto pImg = (AssetManager::GetInstance().GetImage(btnImg->getAssetFileName())).lock();

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

		g->DrawImage(pImg.get(), coverImg, btnImg->getImgRC().X, btnImg->getImgRC().Y, btnImg->getImgRC().Width, btnImg->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);

		g->SetCompositingMode(CompositingMode::CompositingModeSourceCopy);
		g->FillPie(&empty, int(-btnImg->getImgRC().Width *0.5f), int(-btnImg->getImgRC().Height * 0.5f), btnImg->getImgRC().Width *2, btnImg->getImgRC().Height * 2, -90, angle);

		pGraphics->DrawImage(&bitmap2, btnImg->getX(), btnImg->getY());
	}
}

void PlayerSkillBtn::Release()
{

}

void PlayerSkillBtn::SendLButtonDown()
{
	if (enable == false)
	{
		return;
	}
	else
	{
		enable = !enable;
	}

	if (Name == "heal")
	{
		for (Character* it : GameManager::GetInstance().curCharacterList)
		{
			if (it->getEnable() == true && it->getVisible() == true)
			{
				// HP를 늘려준다
				it->hp += 200;
					
				// 이펙트 실행
				Effect* skillEffect = new Effect();
				skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
				XmlManager::GetInstance().ParseEffectData(*skillEffect);
				skillEffect->setX(it->getX());
				skillEffect->setY(it->getY() - 80);
				skillEffect->Init(new EffectGraphicsComponent(skillEffect));

				SceneManager::GetInstance().GetCurScene()->addToInfoObj(skillEffect);
			}
		}
	}
	else if (Name == "blizzard")
	{
		for (Character* it : GameManager::GetInstance().curEnemyList)
		{
			if (it->getEnable() == true && it->getVisible() == true)
			{
				// 공격한다
				it->hp -= 200;

				// 이펙트 실행
				Effect* skillEffect = new Effect();
				skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
				XmlManager::GetInstance().ParseEffectData(*skillEffect);
				skillEffect->setX(it->getX());
				skillEffect->setY(it->getY() - 80);
				skillEffect->Init(new EffectGraphicsComponent(skillEffect));

				SceneManager::GetInstance().GetCurScene()->addToInfoObj(skillEffect);
			}
		}
	}
	else if (Name == "razer")
	{
		//이펙트 실행
		Effect* skillEffect = new Effect();
		skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
		XmlManager::GetInstance().ParseEffectData(*skillEffect);
		skillEffect->setX(GameManager::GetInstance().CommandPlayer->getX() + 800);
		skillEffect->setY(GameManager::GetInstance().CommandPlayer->getY() - 100);
		skillEffect->Init(new EffectGraphicsComponent(skillEffect));

		SceneManager::GetInstance().GetCurScene()->addToInfoObj(skillEffect);

		for (Character* it : GameManager::GetInstance().curEnemyList)
		{
			if (it->getEnable() == true && it->getVisible() == true)
			{
				int minX = skillEffect->getX() - (skillEffect->frameWidth / 2);
				int maxX = minX + skillEffect->frameWidth;
				if (minX < it->getX() && it->getX() < maxX)
				{
					// 만약에 레이저의 범위 안에 적이 존재하면
					//공격한다
					printf("comm : %d, 적 : %d \n", GameManager::GetInstance().CommandPlayer->getX(), it->getX());
					printf("%s 이 맞음 HP : %d \n", it->name, it->hp);
					it->hp -= 400;
				}
			}
		}
	}

}