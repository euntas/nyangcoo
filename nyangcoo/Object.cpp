#include "pch.h"
#include "Object.h"

Object::Object()
	: Objtype(eObjectType_None)
	, Enable(true)
	, bleft(true)
	, Visible(true)
{

}

Object::Object(EObjectType InType)
	: Objtype(InType)
	, Enable(true)
	, bleft(true)
	, Visible(true)
{

}

void Object::Init()
{
	Enable = true;
	Visible = true;
}

void Object::Init(InputComponent* input, GraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;
}

void Object::setEnable(bool flag)
{
	Enable = flag;
}

void Object::Update(float Delta)
{
	//input_->update(this);
	// 플레이어일 경우
	if (Objtype == eObjectType_Player)
	{
		graphics_->update(Delta);
	}
	else
	{
		graphics_->update(Delta);
	}
}

void Object::Render(Gdiplus::Graphics* pGraphics)
{
	graphics_->render(pGraphics);
}

void Object::Release() 
{

}