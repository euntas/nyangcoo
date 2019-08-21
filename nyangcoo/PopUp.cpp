#include "pch.h"
#include "PopUp.h"

PopUp::PopUp() : StaticObject(EObjectType::eObjectType_PopUp)
{

}

PopUp::PopUp(EPopup _name) : StaticObject(EObjectType::eObjectType_PopUp)
{
	name = _name;

	this->x = 585;
	this->y = 197;

	if (name == ePopup_close)
	{
		bg = new StaticObject();
		bg->Objtype = eObjectType_BGImage;
		bg->AssetFileName = TEXT("popup_background.png");
		bg->ImgRC = Rect(0, 0, 250, 198);
		bg->ViewRC = bg->ImgRC;
		bg->ViewRC.X = x;
		bg->ViewRC.Y = y;

		infoStaticObj.emplace_back(bg);

		Btn* LoadTitleBtn = new Btn();
		LoadTitleBtn->ID = eScene_Exit;
		LoadTitleBtn->AssetFileName = TEXT("popup_loadtitle.png");
		LoadTitleBtn->ImgRC = Rect(0, 0, 227, 45);
		LoadTitleBtn->ViewRC = LoadTitleBtn->ImgRC;
		LoadTitleBtn->x = 12;
		LoadTitleBtn->y = 80;
		LoadTitleBtn->ViewRC.X = x + LoadTitleBtn->x;
		LoadTitleBtn->ViewRC.Y = y + LoadTitleBtn->y;

		infoStaticObj.emplace_back(LoadTitleBtn);

		Btn* BackTitleBtn = new Btn();
		BackTitleBtn->ID = eScene_Exit;
		BackTitleBtn->AssetFileName = TEXT("popup_backtitle.png");
		BackTitleBtn->ImgRC = Rect(0, 0, 227, 45);
		BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
		BackTitleBtn->x = 12;
		BackTitleBtn->y = 135;
		BackTitleBtn->ViewRC.X = x + BackTitleBtn->x;
		BackTitleBtn->ViewRC.Y = y + BackTitleBtn->y;

		infoStaticObj.emplace_back(BackTitleBtn);

		Visible = false;
	}
	else if (name == ePopup_result)
	{
		bg = new StaticObject();
		bg->Objtype = eObjectType_BGImage;
		bg->AssetFileName = TEXT("result_win.png");
		bg->ImgRC = Rect(0, 0, 271, 219);
		bg->ViewRC = bg->ImgRC;
		bg->ViewRC.X = x;
		bg->ViewRC.Y = y;

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn();
		BackTitleBtn->ID = eScene_Script;
		BackTitleBtn->AssetFileName = TEXT("continue_btn.png");
		BackTitleBtn->ImgRC = Rect(0, 0, 212, 62);
		BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
		BackTitleBtn->x = 30;
		BackTitleBtn->y = 138;
		BackTitleBtn->ViewRC.X = x + BackTitleBtn->x;
		BackTitleBtn->ViewRC.Y = y + BackTitleBtn->y;

		infoStaticObj.emplace_back(BackTitleBtn);

		Visible = false;
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

		if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game" && name != ePopup_result)
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

			pGraphics->DrawImage(pImg.get(), it->ViewRC, it->ImgRC.X, it->ImgRC.Y, it->ImgRC.Width, it->ImgRC.Height, Gdiplus::Unit::UnitPixel,
				&attr, 0, nullptr);
		}
		else
		{
			pGraphics->DrawImage(pImg.get(), it->ViewRC, it->ImgRC.X, it->ImgRC.Y, it->ImgRC.Width, it->ImgRC.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

void PopUp::Release()
{

}
