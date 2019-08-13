#include "pch.h"
#include "PopUp.h"

PopUp::PopUp() : StaticObject(EObjectType::eObjectType_PopUp)
{
	/*this->x = 630;
	this->y = 10;

	name = ePopup_close;

	

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("popup_all.png");
	bg->rc = Rect(0, 0, 250, 198);

	infoStaticObj.emplace_back(bg);

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	BackTitleBtn->AssetFileName = TEXT("popup_gotitle.png");
	BackTitleBtn->rc = Rect(0, 0, 227, 45);
	BackTitleBtn->x = 12;
	BackTitleBtn->y = 136;

	infoStaticObj.emplace_back(BackTitleBtn);*/

}

PopUp::PopUp(EPopup name) : StaticObject(EObjectType::eObjectType_PopUp)
{
	if (name == ePopup_close)
	{
		this->x = 630;
		this->y = 10;

		name = ePopup_close;

		bg = new StaticObject();
		bg->Objtype = eObjectType_BGImage;
		bg->AssetFileName = TEXT("popup_background.png");
		bg->rc = Rect(0, 0, 250, 198);

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn();
		BackTitleBtn->ID = eScene_Start;
		//BackTitleBtn->ID = eScene_Exit;
		BackTitleBtn->AssetFileName = TEXT("popup_gotitle.png");
		BackTitleBtn->rc = Rect(0, 0, 227, 45);
		BackTitleBtn->x = 12;
		BackTitleBtn->y = 135;

		infoStaticObj.emplace_back(BackTitleBtn);

		//Visible = false;
	}
	

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
	if (Visible == false)
		return;

	for (auto& it : infoStaticObj)
	{
		if (it->Visible == false) return;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();

		if (it->Objtype == eObjectType_BGImage) // 배경 그림
		{
			Rect tempRC(x, y, rc.Width, rc.Height);
			pGraphics->DrawImage(pImg.get(), tempRC, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
		else // 그 외 그림
		{
			Rect tempRC(x + it->x, y + it->y, it->rc.Width, it->rc.Height);
			pGraphics->DrawImage(pImg.get(), tempRC, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

void PopUp::Release()
{

}
