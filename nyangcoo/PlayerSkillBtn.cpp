#include "pch.h"
#include "PlayerSkillBtn.h"

PlayerSkillBtn::PlayerSkillBtn()
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{

}

PlayerSkillBtn::PlayerSkillBtn(std::string skillName)
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{
	Enable = false;

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
	btnImg->AssetFileName.assign(imgFilename.begin(), imgFilename.end());
	btnImg->ImgRC = Gdiplus::Rect(0, 0, 127, 144);
	btnImg->ViewRC = btnImg->ImgRC;
}

void PlayerSkillBtn::Update(float Delta)
{
	if (Enable == false)
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
			angle += 3;
		}
	}

	if (angle == 360)
	{
		angle = 0;
		Enable = true;
	}
}

void PlayerSkillBtn::Render(Gdiplus::Graphics* pGraphics)
{
	btnImg->Render(pGraphics);

	// 쿨타임 관련
	Gdiplus::SolidBrush gray(Color(128, 0, 0, 0));
	Gdiplus::SolidBrush empty(Color(0, 0, 0, 0));

	if (Enable == false)
	{
		Rect coverImg(0, 0, btnImg->ImgRC.Width, btnImg->ImgRC.Height);
		Gdiplus::Bitmap bitmap2(coverImg.Width, coverImg.Height, PixelFormat32bppARGB);
		Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(&bitmap2);

		auto pImg = (AssetManager::GetInstance().GetImage(btnImg->AssetFileName)).lock();

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

		g->DrawImage(pImg.get(), coverImg, btnImg->ImgRC.X, btnImg->ImgRC.Y, btnImg->ImgRC.Width, btnImg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);

		g->SetCompositingMode(CompositingMode::CompositingModeSourceCopy);
		g->FillPie(&empty, int(-btnImg->ImgRC.Width *0.5f), int(-btnImg->ImgRC.Height * 0.5f), btnImg->ImgRC.Width *2, btnImg->ImgRC.Height * 2, -90, angle);

		pGraphics->DrawImage(&bitmap2, btnImg->x, btnImg->y);
	}
}

void PlayerSkillBtn::Release()
{

}

void PlayerSkillBtn::SendLButtonDown()
{
	if (Enable == false)
	{
		return;
	}
	else
	{
		Enable = !Enable;
	}

	if (Name == "heal")
	{
		for (Character* it : GameManager::GetInstance().curCharacterList)
		{
			if (it->Enable == true && it->Visible == true)
			{
				// HP를 늘려준다
				it->hp += 200;
					
				// 이펙트 실행
				Effect* skillEffect = new Effect();
				skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
				XmlManager::GetInstance().ParseEffectData(*skillEffect);
				skillEffect->x = it->x;
				skillEffect->y = it->y - 80;
				skillEffect->Init(new EffectGraphicsComponent(skillEffect));

				SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(skillEffect);
			}
		}
	}
	else if (Name == "blizzard")
	{
		for (Character* it : GameManager::GetInstance().curEnemyList)
		{
			if (it->Enable == true && it->Visible == true)
			{
				// 공격한다
				it->hp -= 200;

				// 이펙트 실행
				Effect* skillEffect = new Effect();
				skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
				XmlManager::GetInstance().ParseEffectData(*skillEffect);
				skillEffect->x = it->x;
				skillEffect->y = it->y - 80;
				skillEffect->Init(new EffectGraphicsComponent(skillEffect));

				SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(skillEffect);
			}
		}
	}
	else if (Name == "razer")
	{
		//이펙트 실행
		Effect* skillEffect = new Effect();
		skillEffect->EffectXmlFileName = "Asset\\effect\\effect_skill_" + Name + ".xml";
		XmlManager::GetInstance().ParseEffectData(*skillEffect);
		/*skillEffect->x = GameManager::GetInstance().CommandPlayer->x + (GameManager::GetInstance().CommandPlayer->frameWidth[0] / 2);
		skillEffect->y = GameManager::GetInstance().CommandPlayer->y + (GameManager::GetInstance().CommandPlayer->frameHeight[0] / 2);*/
		skillEffect->x = 2 * (GameManager::GetInstance().CommandPlayer->x + GameManager::GetInstance().CommandPlayer->frameWidth[0]);
		skillEffect->y = GameManager::GetInstance().CommandPlayer->y - 100;
		skillEffect->Init(new EffectGraphicsComponent(skillEffect));

		SceneManager::GetInstance().GetCurScene()->infoObj.emplace_back(skillEffect);

		for (Character* it : GameManager::GetInstance().curEnemyList)
		{
			if (it->Enable == true && it->Visible == true)
			{
				if (skillEffect->x < it->x && it->x < skillEffect->x + skillEffect->frameWidth)
				{
					// 만약에 레이저의 범위 안에 적이 존재하면
					//공격한다
					printf("comm : %d, 적 : %d \n", GameManager::GetInstance().CommandPlayer->x, it->x);
					printf("%s 이 맞음 HP : %d \n", it->name, it->hp);
					it->hp -= 400;
				}
			}
		}
	}

}