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
		bg->ImgRC = Rect(0, 0, 271, 279);
		bg->ViewRC = bg->ImgRC;
		bg->ViewRC.X = x;
		bg->ViewRC.Y = y;

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn();
		BackTitleBtn->ID = eScene_Start;
		BackTitleBtn->AssetFileName = TEXT("popup_backtomain.png");
		BackTitleBtn->ImgRC = Rect(0, 0, 212, 62);
		BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
		BackTitleBtn->x = 30;
		BackTitleBtn->y = 126;
		BackTitleBtn->ViewRC.X = x + BackTitleBtn->x;
		BackTitleBtn->ViewRC.Y = y + BackTitleBtn->y;

		infoStaticObj.emplace_back(BackTitleBtn);

		Btn* GameOverBtn = new Btn();
		GameOverBtn->ID = eScene_Exit;
		GameOverBtn->AssetFileName = TEXT("popup_gameover.png");
		GameOverBtn->ImgRC = Rect(0, 0, 212, 62);
		GameOverBtn->ViewRC = GameOverBtn->ImgRC;
		GameOverBtn->x = 30;
		GameOverBtn->y = 194;
		GameOverBtn->ViewRC.X = x + GameOverBtn->x;
		GameOverBtn->ViewRC.Y = y + GameOverBtn->y;

		infoStaticObj.emplace_back(GameOverBtn);

		Visible = false;
	}
	else if (name == ePopup_result)
	{
		this->x = 410;
		this->y = 100;

		bg = new StaticObject();
		bg->Objtype = eObjectType_BGImage;
		bg->AssetFileName = TEXT("result_win.png");
		bg->ImgRC = Rect(0, 0, 600, 400);
		bg->ViewRC = bg->ImgRC;
		bg->ViewRC.X = x;
		bg->ViewRC.Y = y;

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn();
		BackTitleBtn->ID = eScene_Script;
		BackTitleBtn->AssetFileName = TEXT("continue_btn.png");
		BackTitleBtn->ImgRC = Rect(0, 0, 237, 69);
		BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
		BackTitleBtn->x = 183;
		BackTitleBtn->y = 304;
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
