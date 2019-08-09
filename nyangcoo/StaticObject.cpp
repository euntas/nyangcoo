#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject()
	: Objtype(eObjectType_None)
	, Enable(true)
{

}

StaticObject::StaticObject(EObjectType InType)
	: Objtype(InType)
	, Enable(true)
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
	if (Enable == false) return;

	auto pImg = (AssetManager::GetInstance().GetImage(AssetFileName)).lock();

	if (Objtype == eObjectType_BGImage) // ��� �׸�
	{
		pGraphics->DrawImage(pImg.get(), SceneManager::GetInstance().ViewRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
	else // �� �� �׸�
	{
		Rect tempRC(x, y, rc.Width, rc.Height);
		pGraphics->DrawImage(pImg.get(), tempRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void StaticObject::Release()
{

}
