#include "pch.h"
#include "AssetManager.h"

AssetManager& AssetManager::GetInstance()
{
	static AssetManager mgr;
	return mgr;
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

	//if (ret.expired())
	//{
	//	auto p = ret.lock();
	//	// 접근은 p-> 이런식으로
	//}

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