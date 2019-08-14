#include "pch.h"
#include "GraphicsComponent.h"

void GraphicsComponent::update(float Delta)
{

}

void GraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	auto pImg = (AssetManager::GetInstance().GetImage(parentObj->AssetFileName)).lock();

	pGraphics->DrawImage(pImg.get(), parentObj->rc, parentObj->rc.X, parentObj->rc.Y, parentObj->rc.Width, parentObj->rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}
