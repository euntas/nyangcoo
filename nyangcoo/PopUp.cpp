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
		bg->setObjtype(eObjectType_BGImage);
		bg->setAssetFileName(TEXT("popup_background.png"));
		bg->setImgRC(Rect(0, 0, 271, 279));
		bg->setViewRC(Rect(x, y, 271, 279));

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn(eScene_Start, TEXT("popup_backtomain.png"), Rect(0, 0, 212, 62), Rect(0, 0, 212, 62), 30, 126, 0);
		BackTitleBtn->setViewRC(Rect(x + BackTitleBtn->getX(), y + BackTitleBtn->getY(), BackTitleBtn->getViewRC().Width, BackTitleBtn->getViewRC().Height));

		infoStaticObj.emplace_back(BackTitleBtn);

		Btn* GameOverBtn = new Btn(eScene_Exit, TEXT("popup_gameover.png"), Rect(0, 0, 212, 62), Rect(0, 0, 212, 62), 30, 194, 0);
		GameOverBtn->setViewRC(Rect(x + GameOverBtn->getX(), y + GameOverBtn->getY(), GameOverBtn->getViewRC().Width, GameOverBtn->getViewRC().Height));

		infoStaticObj.emplace_back(GameOverBtn);

		visible = false;
	}
	else if (name == ePopup_result)
	{
		this->x = 410;
		this->y = 100;

		bg = new StaticObject();
		bg->setObjtype(eObjectType_BGImage);
		bg->setAssetFileName(TEXT("result_win.png"));
		bg->setImgRC(Rect(0, 0, 600, 400));
		bg->setViewRC(Rect(x, y, 600, 400));

		infoStaticObj.emplace_back(bg);

		Btn* BackTitleBtn = new Btn(eScene_Script, TEXT("continue_btn.png"), Rect(0, 0, 237, 69), Rect(x + 183, y + 304, 237, 69), 183, 304, 0);

		infoStaticObj.emplace_back(BackTitleBtn);

		visible = false;
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
	if (visible == false)
		return;

	for (auto& it : infoStaticObj)
	{
		if (it->getVisible() == false) return;

		auto pImg = (AssetManager::GetInstance().GetImage(it->getAssetFileName())).lock();

		if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game" && name != ePopup_result)
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

			pGraphics->DrawImage(pImg.get(), it->getViewRC(), it->getImgRC().X, it->getImgRC().Y, it->getImgRC().Width, it->getImgRC().Height, Gdiplus::Unit::UnitPixel,
				&attr, 0, nullptr);
		}
		else
		{
			pGraphics->DrawImage(pImg.get(), it->getViewRC(), it->getImgRC().X, it->getImgRC().Y, it->getImgRC().Width, it->getImgRC().Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

void PopUp::Release()
{

}
