#include "pch.h"
#include "Effect.h"

Effect::Effect()
	: Object(eObjectType_Effect)
{

}

void Effect::Init(EffectGraphicsComponent* graphics)
{
	graphics_ = graphics;

	Effect::setEffectPos(700, 420);

	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->Init(frameWidth, frameHeight, frameNum, frameDelta, spriteRowNum, imgNumPerLine);
}

void Effect::Update(float Delta)
{
	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->update(this, Delta);
}

void Effect::Render(Gdiplus::Graphics* pGraphics)
{
	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->render(this, pGraphics);
}

void Effect::Release()
{

}

void Effect::setEffectPos(int x, int y)
{
	this->x = x;
	this->y = y;
}