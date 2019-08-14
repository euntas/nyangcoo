#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
	: Object(eObjectType_Enemy)
{
	bleft = false;
}

void Enemy::Init()
{
	Enable = true;
	Visible = true;

	DeltaA = 0;

	Enemy::setEnemyPos(1000, 520);

	XmlManager::GetInstance().ParseEnemyInitData(*this);

	curState = eState_Run;

	AssetFileName = EnemyAssetFileName[curState];

	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	enemyGraphics_->Init();
}

void Enemy::Init(InputComponent* input, PlayerGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Init();
}

void Enemy::Update(float Delta)
{
	// 내 HP 상태 확인
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// 플레이어들과 위치 비교
	vector<Player*> colPlayer; // 충돌한 플레이어들 저장용
	colPlayer.clear();
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it == nullptr) continue;

		if (it->Objtype == eObjectType_Player && it->Enable)
		{
			Player* p = reinterpret_cast<Player*>(it);
			float dist = pow(x - it->x - 2, 2) + pow(y - it->y - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + p->frameWidth[eState_Run] / 2), 2);

			// 적과 충돌
			if (dist <= rad)
			{
				colPlayer.emplace_back(p);
				
				break;
			}
		}
	}

	// 저장된 적이 있다면 hit으로 상태변화
	if (colPlayer.size() > 0)
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
			this->x--;
		}
	}
	else if (curState == eState_Hit)
	{
		if (DeltaA > atkSpeed)
		{
			DeltaA = 0;
			for (auto& it : colPlayer)
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
	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	enemyGraphics_->update(Delta);
}

void Enemy::Render(Gdiplus::Graphics* pGraphics)
{
	if (this == nullptr) return;
	if (pGraphics == nullptr) return;

	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	
	enemyGraphics_->render(pGraphics);
}

void Enemy::Release()
{
	
}

bool Enemy::CheckDestroy()
{
	if (Enable == false && Visible == false)
	{
		return true;
	}
	
	return false;
}

void Enemy::setEnemyPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Enemy::changeState(EState state)
{
	if (curState == eState_Dead)
		return;

	curState = state;
	AssetFileName = EnemyAssetFileName[curState];

	// 현재 state에 맞게 바꿔준다.
	//enemyGraphics_->InitParams();
}