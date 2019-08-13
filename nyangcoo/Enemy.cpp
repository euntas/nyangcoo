#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
	: Object(eObjectType_Enemy)
{
	bleft = false;
}

void Enemy::Init()
{
	DeltaA = 0;

	Enemy::setEnemyPos(1000, 520);

	XmlManager::GetInstance().ParseEnemyInitData(*this);

	curState = eState_Run;

	AssetFileName = EnemyAssetFileName[curState];

	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	enemyGraphics_->Init(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}

void Enemy::Init(InputComponent* input, PlayerGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Init();
}

void Enemy::Update(float Delta)
{
	// �� HP ���� Ȯ��
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// �÷��̾��� ��ġ ��
	vector<Player*> colPlayer; // �浹�� �÷��̾�� �����
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it->Objtype == eObjectType_Player)
		{
			Player* p = reinterpret_cast<Player*>(it);
			float dist = pow(x - it->x - 2, 2) + pow(y - it->y - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + p->frameWidth[eState_Run] / 2), 2);

			// ���� �浹
			if (dist <= rad)
			{
				colPlayer.emplace_back(p);
				//changeState(eState_Hit);
				
				break;
			}
		}
	}

	// ����� ���� �ִٸ� hit���� ���º�ȭ
	if (colPlayer.size() > 0)
	{
		changeState(eState_Hit);
	}

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
				// ����
				it->hp -= atk;
				printf("%s �� %s �� %d ���� [%s HP : %d]\n", name.c_str(), it->name.c_str(), atk, it->name.c_str(), it->hp);
			}
		}
	}
	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	enemyGraphics_->update(this, Delta);
}

void Enemy::Render(Gdiplus::Graphics* pGraphics)
{
	enemyGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	
	enemyGraphics_->render(this, pGraphics);
}

void Enemy::Release()
{
	if (hp <= 0)
	{
		//delete this;
		//this->Enable = false;
	}
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

	// ���� state�� �°� �ٲ��ش�.
	enemyGraphics_->InitParams(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}