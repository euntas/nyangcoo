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

void Object::Update(Graphics& graphics, float Delta)
{
	input_->update(*this);
	graphics_->update(*this, graphics, Delta);
}

void Object::Release() 
{

}