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
	//curState = eState_Damage;
	//curState = eState_Dead;

	// TODO. ���� xml���� �о�;� �� 
	/*frameWidth[eState_Run] = 121;
	frameHeight[eState_Run] = 165;
	frameNum[eState_Run] = 4;
	frameDelta[eState_Run] = 150.0f;*/

	frameWidth[eState_Run] = 170;
	frameHeight[eState_Run] = 170;
	frameNum[eState_Run] = 4;
	frameDelta[eState_Run] = 150.0f;
	spriteRowNum[eState_Run] = 1;
	imgNumPerLine[eState_Run] = 4;

	frameWidth[eState_Damage] = 170;
	frameHeight[eState_Damage] = 170;
	frameNum[eState_Damage] = 8;
	frameDelta[eState_Damage] = 150.0f;
	spriteRowNum[eState_Damage] = 3;
	imgNumPerLine[eState_Damage] = 3;

	frameWidth[eState_Dead] = 170;
	frameHeight[eState_Dead] = 170;
	frameNum[eState_Dead] = 5;
	frameDelta[eState_Dead] = 150.0f;
	spriteRowNum[eState_Dead] = 1;
	imgNumPerLine[eState_Dead] = 5;

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