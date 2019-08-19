#include "pch.h"
#include "PlayerSkillBtn.h"

PlayerSkillBtn::PlayerSkillBtn()
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{

}

PlayerSkillBtn::PlayerSkillBtn(std::string skillName)
	: StaticObject(EObjectType::eObjectType_PlayerSkillBtn)
{
	Name = skillName;

	std::string imgFilename;

	imgFilename = "skill_" + skillName + ".png";

	if (skillName == "heal")
	{	
		skillType = eSkill_Heal;
	}
	else if (skillName == "blizzard")
	{
		skillType = eSkill_Blizzard;
	}
		
	btnImg = new StaticObject();
	btnImg->AssetFileName.assign(imgFilename.begin(), imgFilename.end());
	btnImg->ImgRC = Gdiplus::Rect(0, 0, 127, 144);
	btnImg->ViewRC = btnImg->ImgRC;
	btnImg->x = 1000 + x;
	btnImg->y = 530 + y;
}

void PlayerSkillBtn::Init()
{

}

void PlayerSkillBtn::Update(float Delta)
{

}

void PlayerSkillBtn::Render(Gdiplus::Graphics* pGraphics)
{
	btnImg->Render(pGraphics);
}

void PlayerSkillBtn::Release()
{

}

void PlayerSkillBtn::SendLButtonDown()
{
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

}