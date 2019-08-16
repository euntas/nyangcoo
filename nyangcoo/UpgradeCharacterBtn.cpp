#include "pch.h"
#include "UpgradeCharacterBtn.h"

UpgradeCharacterBtn::UpgradeCharacterBtn(MakeCharacterBtn* parent)
	: StaticObject(EObjectType::eObjectType_UpgradeCharacterBtn)
{
	parentMakeBtn = parent;

	this->x = parent->x;
	this->y = parent->y - 34;

	this->rc = Gdiplus::Rect(0, 0, 85, 34);

	upgradeCost = 100;

	std::string fn = "slot\\up_slot_" + std::to_string(upgradeCost) + ".png";
	this->AssetFileName.assign(fn.begin(), fn.end());
}

void UpgradeCharacterBtn::Init()
{

}

void UpgradeCharacterBtn::Update(float Delta)
{

}

void UpgradeCharacterBtn::Render(Gdiplus::Graphics* pGraphics)
{
	if (Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(AssetFileName)).lock();

	Rect tempRC(x, y, rc.Width, rc.Height);
	pGraphics->DrawImage(pImg.get(), tempRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}

void UpgradeCharacterBtn::Release()
{

}

void UpgradeCharacterBtn::SendLButtonDown()
{
	// TODO. 골드가 upgradeCost 이상일때만 실행해야 함.
	parentMakeBtn->atk += 50;
}
