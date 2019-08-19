#include "pch.h"
#include "GraphicsComponent.h"

void GraphicsComponent::update(float Delta)
{

}

void GraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	auto pImg = (AssetManager::GetInstance().GetImage(parentObj->AssetFileName)).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
	{
		//gray scale conversion:
		Gdiplus::ColorMatrix matrix =
		{
			.3f, .3f, .3f,   0,   0,
			.6f, .6f, .6f,   0,   0,
			.1f, .1f, .1f,   0,   0,
			0,   0,   0,   1,   0,
			0,   0,   0,   0,   1
		};

		Gdiplus::ImageAttributes attr;
		attr.SetColorMatrix(&matrix,
			Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		pGraphics->DrawImage(pImg.get(), parentObj->rc, parentObj->rc.X, parentObj->rc.Y, parentObj->rc.Width, parentObj->rc.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), parentObj->rc, parentObj->rc.X, parentObj->rc.Y, parentObj->rc.Width, parentObj->rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}
