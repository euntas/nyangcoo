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
}

void Player::Update(float Delta)
{
	playerGraphics_ = reinterpret_cast<PlayerGraphicsComponent*>(graphics_);
	// TODO. 임의로 숫자 설정함. 나중에 xml 읽어와서 바꿔야 함
	playerGraphics_->Init(121, 165, 4, Delta);
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