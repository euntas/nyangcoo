#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject()
	: Objtype(eObjectType_None)
	, Visible(true)
{

}

StaticObject::StaticObject(EObjectType InType)
	: Objtype(InType)
	, Visible(true)
{

}

void StaticObject::Init()
{

}

void StaticObject::Update(float Delta)
{

}

void StaticObject::Render(Gdiplus::Graphics* pGraphics)
{
	if (Visible == false) return;

	auto pImg = (AssetManager::GetInstance().GetImage(AssetFileName)).lock();

	if (Objtype == eObjectType_BGImage) // 배경 그림
	{
		pGraphics->DrawImage(pImg.get(), SceneManager::GetInstance().ViewRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
	else // 그 외 그림
	{
		Rect tempRC(x, y, ViewRC.Width, ViewRC.Height);
		int AddX = (tempRC.Width - ImgRC.Width) * 0.5f;
		int AddY = (tempRC.Height - ImgRC.Height) * 0.5f;
		tempRC.X -= AddX;
		tempRC.Y -= AddY;
		pGraphics->DrawImage(pImg.get(), tempRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void StaticObject::Release()
{

}
