#include "pch.h"
#include "Object.h"

Object::Object()
	: objtype(eObjectType_None)
	, enable(true)
	, bleft(true)
	, visible(true)
{

}

Object::Object(EObjectType InType)
	: objtype(InType)
	, enable(true)
	, bleft(true)
	, visible(true)
{

}

void Object::Init()
{
	enable = true;
	visible = true;
}

void Object::Init(InputComponent* input, GraphicsComponent* graphics)
{
	input_ = input;
	graphics_ = graphics;
}

void Object::Update(float Delta)
{
	// 플레이어일 경우
	if (objtype == eObjectType_Player)
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

std::wstring Object::getAssetFileName()
{
	return assetFileName;
}

void Object::setAssetFileName(std::wstring _assetFileName)
{
	assetFileName = _assetFileName;
}

Gdiplus::Rect Object::getRc()
{
	return rc;
}

void Object::setRc(Gdiplus::Rect _rc)
{
	rc = _rc;
}

EObjectType Object::getObjtype()
{
	return objtype;
}

void Object::setObjtype(EObjectType _objtype)
{
	objtype = _objtype;
}

bool Object::getEnable()
{
	return enable;
}

void Object::setEnable(bool _enable)
{
	enable = _enable;
}

bool Object::getVisible()
{
	return visible;
}

void Object::setVisible(bool _visible)
{
	visible = _visible;
}

bool Object::getBleft()
{
	return bleft;
}

void Object::setBleft(bool _bleft)
{
	bleft = _bleft;
}

int Object::getX()
{
	return x;
}

void Object::setX(int _x)
{
	x = _x;
}

int Object::getY()
{
	return y;
}

void Object::setY(int _y)
{
	y = _y;
}