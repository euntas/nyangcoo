#include "pch.h"
#include "GraphicsComponent.h"

void GraphicsComponent::update(float Delta)
{

}

void GraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	auto pImg = (AssetManager::GetInstance().GetImage(parentObj->getAssetFileName())).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		pGraphics->DrawImage(pImg.get(), parentObj->getRc(), parentObj->getRc().X, parentObj->getRc().Y, parentObj->getRc().Width, parentObj->getRc().Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), parentObj->getRc(), parentObj->getRc().X, parentObj->getRc().Y, parentObj->getRc().Width, parentObj->getRc().Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}
