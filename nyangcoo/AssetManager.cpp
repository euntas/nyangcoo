#include "pch.h"
#include "AssetManager.h"

AssetManager& AssetManager::GetInstance()
{
	static AssetManager mgr;
	return mgr;
}

AssetManager::AssetManager()
{
	// grayscale관련 변수 설정
	grayScaleMatrix =
	{
		.3f, .3f, .3f,   0,   0,
		.6f, .6f, .6f,   0,   0,
		.1f, .1f, .1f,   0,   0,
		0,   0,   0,   1,   0,
		0,   0,   0,   0,   1
	};

	grayScaleAttr->SetColorMatrix(&grayScaleMatrix,
		Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);
}

Gdiplus::ImageAttributes* AssetManager::getGrayScaleAttr()
{
	return grayScaleAttr;
}

AssetManager::~AssetManager()
{
	delete grayScaleAttr;

	for (auto& it : imgDic)
	{
		it.second.reset();
	}
	imgDic.clear();
}

std::weak_ptr<Gdiplus::Image> AssetManager::GetImage(std::wstring str)
{
	std::hash<std::wstring> a;
	std::weak_ptr<Gdiplus::Image> ret;
	auto it = imgDic.find(a(str));
	if (it == imgDic.end())
		ret = MyLoadImage(str);
	else
	{
		ret = it->second;
	}

	return ret;
}

std::weak_ptr<Gdiplus::Image> AssetManager::MyLoadImage(std::wstring str)
{
	std::wstring temp(TEXT("Asset\\"));
	temp.append(str);
	std::shared_ptr<Gdiplus::Image> Img(new Gdiplus::Image(temp.c_str()));
	std::hash<std::wstring> a;
	imgDic.insert(std::make_pair(a(str), Img));
	return Img;
}