#include "pch.h"
#include "Player.h"

Player::Player()
	: Object(eObjectType_Player)
{

}

void Player::Init(InputComponent* input, PlayerGraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;

	Player::setPlayerPos(250, 620);

	curState = eState_Run;
	//curState = eState_Damage;
	//curState = eState_Dead;

	AssetFileName = PlayerAssetFileName[curState];

	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->Init(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState], spriteRowNum[curState], imgNumPerLine[curState]);
}

void Player::Update(float Delta)
{
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

}

void Player::setPlayerPos(int x, int y)
{
	this->x = x;
	this->y = y;
}