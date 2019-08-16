#include "pch.h"
#include "UpgradeCharacterBtn.h"

UpgradeCharacterBtn::UpgradeCharacterBtn(MakeCharacterBtn* parent)
	: StaticObject(EObjectType::eObjectType_UpgradeCharacterBtn)
{
	parentMakeBtn = parent;

	this->x = parent->x;
	this->y = parent->y - 34;

	this->ImgRC = Gdiplus::Rect(0, 0, 85, 34);
	ViewRC = ImgRC;
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

	Rect tempRC(x, y, ViewRC.Width, ViewRC.Height);
	pGraphics->DrawImage(pImg.get(), tempRC, ImgRC.X, ImgRC.Y, ImgRC.Width, ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}

void UpgradeCharacterBtn::Release()
{

}

void UpgradeCharacterBtn::SendLButtonDown()
{
	// TODO. ��尡 upgradeCost �̻��϶��� �����ؾ� ��.
	parentMakeBtn->atk += 50;
}