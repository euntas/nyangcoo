#pragma once
class AssetManager
{
public:
	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	static AssetManager& GetInstance();
	AssetManager();
	~AssetManager();

	Gdiplus::ImageAttributes* getGrayScaleAttr();

private:
	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring str);

	//gray scale conversion:
	Gdiplus::ColorMatrix grayScaleMatrix;
	Gdiplus::ImageAttributes* grayScaleAttr = ::new Gdiplus::ImageAttributes();

private:
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
};

