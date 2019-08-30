#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject()
	: objtype(eObjectType_None)
	, visible(true)
	, enable(true)
{

}

StaticObject::StaticObject(EObjectType InType)
	: objtype(InType)
	, visible(true)
	, enable(true)
{

}

void StaticObject::Init()
{

}

void StaticObject::Update(float Delta)
{

}

void StaticObject::Render(Gdiplus::Graphics* pGraphics)
{
	if (visible == false) return;

	auto pImg = (AssetManager::GetInstance().GetImage(assetFileName)).lock();

	if (objtype == eObjectType_BGImage) // 배경 그림
	{
		if (SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
		{
			GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());
			Gdiplus::Rect tempRC = gs->bg->viewRC;

			if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
			{
				pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, gs->bg->viewRC.Width, gs->bg->viewRC.Height, Gdiplus::Unit::UnitPixel,
					AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
			}
			else
			{
				pGraphics->DrawImage(pImg.get(), tempRC, imgRC.X, imgRC.Y, gs->bg->viewRC.Width, gs->bg->viewRC.Height, Gdiplus::Unit::UnitPixel,
					nullptr, 0, nullptr);
			}
		}
		else
		{
			pGraphics->DrawImage(pImg.get(), viewRC, imgRC.X, imgRC.Y, viewRC.Width, viewRC.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
	else // 그 외 그림
	{
		Rect tempRC(x, y, viewRC.Width, viewRC.Height);
		int AddX = (tempRC.Width - imgRC.Width) * 0.5f;
		int AddY = (tempRC.Height - imgRC.Height) * 0.5f;
		tempRC.X -= AddX;
		tempRC.Y -= AddY;

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
	}
}

void StaticObject::Release()
{

}

std::wstring StaticObject::getAssetFileName()
{
	return assetFileName;
}

void StaticObject::setAssetFileName(std::wstring _assetFileName)
{
	assetFileName = _assetFileName;
}

Gdiplus::Rect StaticObject::getImgRC()
{
	return imgRC;
}

void StaticObject::setImgRC(Gdiplus::Rect _rc)
{
	imgRC = _rc;
}

Gdiplus::Rect StaticObject::getViewRC()
{
	return viewRC;
}

void StaticObject::setViewRC(Gdiplus::Rect _rc)
{
	viewRC = _rc;
}

EObjectType StaticObject::getObjtype()
{
	return objtype;
}

void StaticObject::setObjtype(EObjectType _objtype)
{
	objtype = _objtype;
}

bool StaticObject::getVisible()
{
	return visible;
}

void StaticObject::setVisible(bool _visible)
{
	visible = _visible;
}

bool StaticObject::getEnable()
{
	return enable;
}

void StaticObject::setEnable(bool _enable)
{
	enable = _enable;
}

int StaticObject::getX()
{
	return x;
}

void StaticObject::setX(int _x)
{
	x = _x;
}

int StaticObject::getY()
{
	return y;
}

void StaticObject::setY(int _y)
{
	y = _y;
}
