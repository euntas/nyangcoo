#pragma once

class StaticObject
{
public:
	StaticObject();
	StaticObject(EObjectType InType);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	// Getter, Setter
	std::wstring getAssetFileName();
	void setAssetFileName(std::wstring _assetFileName);

	Gdiplus::Rect getImgRC();
	void setImgRC(Gdiplus::Rect _rc);

	Gdiplus::Rect getViewRC();
	void setViewRC(Gdiplus::Rect _rc);

	EObjectType getObjtype();
	void setObjtype(EObjectType _objtype);

	bool getVisible();
	void setVisible(bool _visible);

	bool getEnable();
	void setEnable(bool _enable);

	int getX();
	void setX(int _x);

	int getY();
	void setY(int _y);

protected:
	std::wstring assetFileName;
	Gdiplus::Rect imgRC;
	Gdiplus::Rect viewRC;
	
	EObjectType objtype;
	bool visible;
	bool enable;

	int x, y;
};

