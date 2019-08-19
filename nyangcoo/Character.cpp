#include "pch.h"
#include "Character.h"

Character::Character()
	: Object(eObjectType_Player)
{

}

Character::Character(EObjectType _objtype)
{
	Objtype = _objtype;

	if (_objtype == eObjectType_Enemy)
	{
		bleft = false;
	}
}

void Character::Init()
{
	Enable = true;
	Visible = true;

	DeltaA = 0;

	if (Objtype == eObjectType_Character)
	{
		setCharacterPos(GameManager::GetInstance().CommandPlayer->x + 78, 520);
	}
	else if (Objtype == eObjectType_Enemy)
	{
		setCharacterPos(GameManager::GetInstance().curStage->bg->ImgRC.Width, 520);
	}
	else
	{
		setCharacterPos(172, 500);
	}
	

	XmlManager::GetInstance().ParseCharacterInitData(*this);

	curState = eState_Run;

	AssetFileName = CharacterAssetFileName[curState];

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
	// �� HP ���� Ȯ��
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// ���� ĳ������ ��� ü���� 200 ���Ϸ� �پ��� damage ������� �ٲ��.
	if (this->Objtype == eObjectType_Player && hp <= 500)
	{
		changeState(eState_Damage);
	}

	// ����� ��ġ ��
	vector<Character*> colEnemy; // �浹�� ���� �����
	colEnemy.clear();
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it == nullptr) continue;

		if (((this->Objtype == eObjectType_Character || this->Objtype == eObjectType_Player) && it->Objtype == eObjectType_Enemy && it->Enable)
			|| (this->Objtype == eObjectType_Enemy && (it->Objtype == eObjectType_Character || it->Objtype == eObjectType_Player) && it->Enable))
		{
			Character* e = reinterpret_cast<Character*>(it);
			float dist = pow(x - it->x - 2, 2) + pow(y - it->y - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + e->frameWidth[eState_Run] / 2), 2);

			// ���� �浹
			if (dist <= rad)
			{
				colEnemy.emplace_back(e);

				break;
			}
		}
	}

	// ����� ���� �ִٸ� hit���� ���º�ȭ
	if (colEnemy.size() > 0)
	{
		changeState(eState_Hit);
	}
	else if (curState != eState_Damage)
	{
		changeState(eState_Run);
	}

	// ���� ���º� ������Ʈ
	DeltaA += Delta;
	if (curState == eState_Run)
	{
		if (DeltaA > speed)
		{
			DeltaA = 0;

			if (Objtype == eObjectType_Character)
			{
				this->x++;
			}
			else if (Objtype == eObjectType_Enemy)
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

				// ����
				if (it->Enable == true)
				{
					it->hp -= atk;
					printf("%s �� %s �� %d ���� [%s HP : %d]\n", name.c_str(), it->name.c_str(), atk, it->name.c_str(), it->hp);

					if (it->hp <= 0)
					{
						it->Enable = false;
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
		Enable = false;
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
	if (Enable == false && Visible == false)
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
	AssetFileName = CharacterAssetFileName[curState];
}