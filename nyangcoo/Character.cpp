#include "pch.h"
#include "Character.h"

Character::Character()
	: Object(eObjectType_Player)
{

}

Character::Character(EObjectType _objtype)
{
	objtype = _objtype;

	if (_objtype == eObjectType_Enemy)
	{
		bleft = false;
	}
}

void Character::Init()
{
	enable = true;
	visible = true;

	DeltaA = 0;

	if (objtype == eObjectType_Character)
	{
		setCharacterPos(GameManager::GetInstance().CommandPlayer->x + 78, 520);
	}
	else if (objtype == eObjectType_Enemy)
	{
		setCharacterPos(GameManager::GetInstance().curStage->bg->ImgRC.Width, 520);
	}
	else
	{
		setCharacterPos(172, 500);
	}
	

	XmlManager::GetInstance().ParseCharacterInitData(*this);

	curState = eState_Run;

	assetFileName = CharacterAssetFileName[curState];

	characterGraphics_ = reinterpret_cast<CharacterGraphicsComponent*>(graphics_);
	characterGraphics_->Init();
}

void Character::Init(InputComponent* input, CharacterGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Init();
}

void Character::Update(float Delta)
{
	// 내 HP 상태 확인
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// 본진 캐릭터일 경우 체력이 200 이하로 줄어들면 damage 모션으로 바뀐다.
	if (this->objtype == eObjectType_Player && hp <= 500)
	{
		changeState(eState_Damage);
	}

	// 적들과 위치 비교
	vector<Character*> colEnemy; // 충돌한 적들 저장용
	colEnemy.clear();
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it == nullptr) continue;

		if (((this->objtype == eObjectType_Character || this->objtype == eObjectType_Player) && it->getObjtype() == eObjectType_Enemy && it->getEnable())
			|| (this->objtype == eObjectType_Enemy && (it->getObjtype() == eObjectType_Character || it->getObjtype() == eObjectType_Player) && it->getEnable()))
		{
			Character* e = reinterpret_cast<Character*>(it);
			float dist = pow(x + atkDist - it->getX() - 2, 2) + pow(y - it->getY() - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + atkDist + e->frameWidth[eState_Run] / 2), 2);

			// 적과 충돌
			if (dist <= rad)
			{
				colEnemy.emplace_back(e);

				break;
			}
		}
	}

	// 저장된 적이 있다면 hit으로 상태변화
	if (colEnemy.size() > 0)
	{
		changeState(eState_Hit);
	}
	else if (curState != eState_Damage)
	{
		changeState(eState_Run);
	}

	// 실제 상태별 업데이트
	DeltaA += Delta;
	if (curState == eState_Run)
	{
		if (DeltaA > speed)
		{
			DeltaA = 0;

			if (objtype == eObjectType_Character)
			{
				this->x++;
			}
			else if (objtype == eObjectType_Enemy)
			{
				this->x--;
			}
		}
	}
	else if (curState == eState_Hit)
	{
		if (DeltaA > atkSpeed)
		{
			DeltaA = 0;
			for (auto& it : colEnemy)
			{
				if (it == nullptr) continue;

				// 공격
				if (it->getEnable() == true)
				{
					it->hp -= atk;
					printf("%s 가 %s 를 %d 공격 [%s HP : %d]\n", name.c_str(), it->name.c_str(), atk, it->name.c_str(), it->hp);

					if (it->hp <= 0)
					{
						it->setEnable(false);
					}
				}
			}
		}
	}
	else if (curState == eState_Damage)
	{
		if (DeltaA > speed)
		{
			DeltaA = 0;
		}
	}
	else if (curState == eState_Dead)
	{
		enable = false;
	}

	characterGraphics_ = reinterpret_cast<CharacterGraphicsComponent*>(graphics_);
	characterGraphics_->update(Delta);
}

void Character::Render(Gdiplus::Graphics* pGraphics)
{
	if (this == nullptr) return;
	if (pGraphics == nullptr) return;

	characterGraphics_ = reinterpret_cast<CharacterGraphicsComponent*>(graphics_);

	characterGraphics_->render(pGraphics);
}

void Character::Release()
{

}

bool Character::CheckDestroy()
{
	if (enable == false && visible == false)
	{
		return true;
	}

	return false;
}

void Character::setCharacterPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Character::changeState(EState state)
{
	CriticalSec cs;

	if (curState == eState_Dead)
		return;
	if (curState == state)
		return;

	curState = state;
	characterGraphics_->ChangeMotion();
	assetFileName = CharacterAssetFileName[curState];
}