#include "pch.h"
#include "Player.h"

Player::Player()
	: Object(eObjectType_Player)
{

}

void Player::Init()
{
	Enable = true;
	Visible = true;

	DeltaA = 0;

	Player::setPlayerPos(250, 520);

	XmlManager::GetInstance().ParsePlayerInitData(*this);

	curState = eState_Run;

	AssetFileName = PlayerAssetFileName[curState];

	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->Init();
}

void Player::Init(InputComponent* input, PlayerGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Init();
}

void Player::Update(float Delta)
{
	// 내 HP 상태 확인
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// 적들과 위치 비교
	vector<Enemy*> colEnemy; // 충돌한 적들 저장용
	colEnemy.clear();
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it == nullptr) continue;

		if (it->Objtype == eObjectType_Enemy && it->Enable)
		{
			Enemy* e = reinterpret_cast<Enemy*>(it);
			float dist = pow(x - it->x - 2, 2) + pow(y - it->y - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + e->frameWidth[eState_Run] / 2), 2);

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
	else
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
			this->x++;
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
				if (it->Enable == true)
				{
					it->hp -= atk;
					printf("%s 가 %s 를 %d 공격 [%s HP : %d]\n", name.c_str(), it->name.c_str(), atk, it->name.c_str(), it->hp);

					if (it->hp <= 0)
					{
						it->Enable = false;
					}
				}
			}
		}
	}
	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->update(Delta);
}

void Player::Render(Gdiplus::Graphics* pGraphics)
{
	if (this == nullptr) return;
	if (pGraphics == nullptr) return;

	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	
	playerGraphics_->render(pGraphics);
}

void Player::Release()
{
	
}

bool Player::CheckDestroy()
{
	if (Enable == false && Visible == false)
	{
		return true;
	}

	return false;
}

void Player::setPlayerPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Player::changeState(EState state)
{
	if (curState == eState_Dead)
		return;

	curState = state;
	AssetFileName = PlayerAssetFileName[curState];

	// 현재 state에 맞게 바꿔준다.
	//playerGraphics_->InitParams(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}