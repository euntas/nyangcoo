#pragma once

class Object
{
public:
	Object();
	Object(EObjectType InType);

	virtual void Init();
	virtual void Init(InputComponent* input, GraphicsComponent* graphics);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	// Getter, Setter
	std::wstring getAssetFileName();
	void setAssetFileName(std::wstring _assetFileName);

	Gdiplus::Rect getRc();
	void setRc(Gdiplus::Rect _rc);

	EObjectType getObjtype();
	void setObjtype(EObjectType _objtype);

	bool getEnable();
	void setEnable(bool _enable);

	bool getVisible();
	void setVisible(bool _visible);

	bool getBleft();
	void setBleft(bool _bleft);

	int getX();
	void setX(int _x);

	int getY();
	void setY(int _y);

protected:
	InputComponent* input_;
	GraphicsComponent* graphics_;

	std::wstring assetFileName;
	Gdiplus::Rect rc;
	EObjectType objtype;
	bool enable;
	bool visible;
	bool bleft;

	int x, y;
};

