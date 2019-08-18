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
		bg->ImgRC = Rect(0, 0, 250, 198);
		bg->ViewRC = bg->ImgRC;
		bg->ViewRC.X = x;
		bg->ViewRC.Y = y;

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn();
		//BackTitleBtn->ID = eScene_Start;
		BackTitleBtn->ID = eScene_Exit;
		BackTitleBtn->AssetFileName = TEXT("popup_backtitle.png");
		BackTitleBtn->ImgRC = Rect(0, 0, 227, 45);
		BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
		BackTitleBtn->x = 12;
		BackTitleBtn->y = 135;
		BackTitleBtn->ViewRC.X = x + BackTitleBtn->x;
		BackTitleBtn->ViewRC.Y = y + BackTitleBtn->y;

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

		pGraphics->DrawImage(pImg.get(), it->ViewRC, it->ImgRC.X, it->ImgRC.Y, it->ImgRC.Width, it->ImgRC.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
	}
}

void PopUp::Release()
{

}
