#include "pch.h"
#include "Effect.h"

Effect::Effect()
	: Object(eObjectType_Effect)
{
	
}

void Effect::Init(EffectGraphicsComponent* graphics)
{
	graphics_ = graphics;

	Effect::setEffectPos(x, y);

	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->Init();

	enable = true;
	visible = true;
}

void Effect::Update(float Delta)
{
	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->update(Delta);
}

void Effect::Render(Gdiplus::Graphics* pGraphics)
{
	effectGraphics_ = reinterpret_cast<EffectGraphicsComponent*>(graphics_);
	effectGraphics_->render(pGraphics);
}

void Effect::Release()
{

}

void Effect::setEffectPos(int x, int y)
{
	this->x = x;
	this->y = y;
}