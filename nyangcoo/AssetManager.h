#pragma once
class AssetManager
{
public:
	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	static AssetManager& GetInstance();

private:
	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring str);

private:
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
};

