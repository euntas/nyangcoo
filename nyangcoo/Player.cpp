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

	this->x = 50;
	this->y = 450;

	curState = eState_Run;
	//curState = eState_Dead;

	// TODO. 추후 xml에서 읽어와야 함 
	/*frameWidth[eState_Run] = 121;
	frameHeight[eState_Run] = 165;
	frameNum[eState_Run] = 4;
	frameDelta[eState_Run] = 150.0f;*/

	frameWidth[eState_Run] = 170;
	frameHeight[eState_Run] = 170;
	frameNum[eState_Run] = 4;
	frameDelta[eState_Run] = 150.0f;

	frameWidth[eState_Dead] = 170;
	frameHeight[eState_Dead] = 170;
	frameNum[eState_Dead] = 5;
	frameDelta[eState_Dead] = 150.0f;

	AssetFileName = PlayerAssetFileName[curState];

	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	playerGraphics_->Init(frameWidth[curState], frameHeight[curState], frameNum[curState], frameDelta[curState]);
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