#include "pch.h"
#include "GraphicsComponent.h"

void GraphicsComponent::update(Object* obj, float Delta)
{

}

void GraphicsComponent::render(Object* obj, Gdiplus::Graphics* pGraphics)
{
	auto pImg = (AssetManager::GetInstance().GetImage(obj->AssetFileName)).lock();

	pGraphics->DrawImage(pImg.get(), obj->rc, obj->rc.X, obj->rc.Y, obj->rc.Width, obj->rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}
