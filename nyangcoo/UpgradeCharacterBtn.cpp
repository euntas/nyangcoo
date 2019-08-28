#include "pch.h"
#include "UpgradeCharacterBtn.h"

UpgradeCharacterBtn::UpgradeCharacterBtn(MakeCharacterBtn* parent)
	: StaticObject(EObjectType::eObjectType_UpgradeCharacterBtn)
{
	parentMakeBtn = parent;

	this->x = parent->getX();
	this->y = parent->getY() - 34;

	this->setImgRC(Gdiplus::Rect(0, 0, 85, 34));
	viewRC = imgRC;
	upgradeCost = 100;

	std::string fn = "slot\\up_slot.png";
	this->assetFileName.assign(fn.begin(), fn.end());
}

void UpgradeCharacterBtn::Init()
{

}

void UpgradeCharacterBtn::Update(float Delta)
{

}

void UpgradeCharacterBtn::Render(Gdiplus::Graphics* pGraphics)
{
	if (visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(assetFileName)).lock();

	Rect tempRC(x, y, viewRC.Width, viewRC.Height);

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, imgRC.Width, imgRC.Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, imgRC.Width, imgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	printCost(pGraphics);
}

void UpgradeCharacterBtn::Release()
{

}

void UpgradeCharacterBtn::SendLButtonDown()
{
	GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

	if (gs->gold >= upgradeCost)
	{
		gs->gold -= upgradeCost;

		parentMakeBtn->atk += 5;
		parentMakeBtn->HP += 20;

		// 코스트 증가시킴
		upgradeCost += 50;
	}
}

void UpgradeCharacterBtn::printCost(Graphics* pGraphics)
{
	Gdiplus::Font F(L"Arial", 5, FontStyleBold, UnitMillimeter);

	PointF P(x + 30, y + 8);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = L"" + std::to_wstring(upgradeCost);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}
