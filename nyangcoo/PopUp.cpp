#include "pch.h"
#include "PopUp.h"

PopUp::PopUp() : StaticObject(EObjectType::eObjectType_PopUp)
{
	this->x = 630;
	this->y = 10;

	name = ePopup_close;

	

	bg = new StaticObject();
	bg->Objtype = eObjectType_PopUp;
	bg->AssetFileName = TEXT("popup_all.png");
	bg->rc = Rect(0, 0, 250, 198);

	infoStaticObj.emplace_back(bg);

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	//BackTitleBtn->AssetFileName = TEXT("popup_gotitle.png");
	BackTitleBtn->rc = Rect(0, 0, 227, 45);
	BackTitleBtn->x = 12;
	BackTitleBtn->y = 136;

	infoStaticObj.emplace_back(BackTitleBtn);

}

void PopUp::Init()
{

}

void PopUp::Update(float Delta)
{
	StaticObject::Update(Delta);
}

void PopUp::Render(Gdiplus::Graphics* pGraphics)
{
	for (auto& it : infoStaticObj)
	{
		if (it->Enable == false) return;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();

		if (Objtype == eObjectType_BGImage) // 배경 그림
		{
			pGraphics->DrawImage(pImg.get(), SceneManager::GetInstance().ViewRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
		else // 그 외 그림
		{
			Rect tempRC(x, y, rc.Width, rc.Height);
			pGraphics->DrawImage(pImg.get(), tempRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

void PopUp::Release()
{

}
