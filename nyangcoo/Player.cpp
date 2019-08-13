#include "pch.h"
#include "Player.h"

Player::Player()
	: Object(eObjectType_Player)
{

}

void Player::Init()
{
	DeltaA = 0;

	Player::setPlayerPos(250, 520);

	XmlManager::GetInstance().ParsePlayerInitData(*this);

	curState = eState_Run;

	AssetFileName = PlayerAssetFileName[curState];

	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->Init(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}

void Player::Init(InputComponent* input, PlayerGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Init();
}

void Player::Update(float Delta)
{
	// �� HP ���� Ȯ��
	if (hp <= 0)
	{
		changeState(eState_Dead);
	}

	// ����� ��ġ ��
	vector<Enemy*> colEnemy; // �浹�� ���� �����
	for (auto& it : SceneManager::GetInstance().GetCurScene()->infoObj)
	{
		if (it->Objtype == eObjectType_Enemy)
		{
			Enemy* e = reinterpret_cast<Enemy*>(it);
			float dist = pow(x - it->x - 2, 2) + pow(y - it->y - 2, 2);
			float rad = pow((frameWidth[eState_Run] / 2 + e->frameWidth[eState_Run] / 2), 2);

			// ���� �浹
			if (dist <= rad)
			{
				colEnemy.emplace_back(e);
				//changeState(eState_Hit);
				
				break;
			}
		}
	}

	// ����� ���� �ִٸ� hit���� ���º�ȭ
	if (colEnemy.size() > 0)
	{
		changeState(eState_Hit);
	}

	// ���� ���º� ������Ʈ
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
				// ����
				it->hp -= atk;
				printf("%s �� %s �� %d ���� [%s HP : %d]\n", name.c_str(), it->name.c_str(), atk, it->name.c_str(), it->hp);
			}
		}
	}
	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->update(this, Delta);
}

void Player::Render(Gdiplus::Graphics* pGraphics)
{
	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	
	playerGraphics_->render(this, pGraphics);
}

void Player::Release()
{
	if (hp <= 0)
	{
		//delete this;
		//this->Enable = false;
	}
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

	// ���� state�� �°� �ٲ��ش�.
	playerGraphics_->InitParams(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}