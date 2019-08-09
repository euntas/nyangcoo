#include "pch.h"
#include "Object.h"

Object::Object()
	: Objtype(eObjectType_None)
	, Enable(true)
{

}

Object::Object(EObjectType InType)
	: Objtype(InType)
	, Enable(true)
{

}

void Object::Init(InputComponent* input, GraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;
}

void Object::Update(float Delta)
{
	//input_->update(this);
	// 플레이어일 경우
	if (Objtype == eObjectType_Player)
	{
		graphics_->update(this, Delta);
	}
}

void Object::Render(Gdiplus::Graphics* pGraphics)
{
	graphics_->render(this, pGraphics);
}

void Object::Release() 
{

}