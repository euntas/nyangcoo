#pragma once

class Object
{
public:
	Object();
	Object(EObjectType InType);

	virtual void Init(InputComponent* input, GraphicsComponent* graphics);

	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void setEnable(bool flag);

	std::wstring AssetFileName;
	Gdiplus::Rect rc;
	EObjectType Objtype;
	bool Enable;

	int x, y;

protected:
	InputComponent* input_;
	GraphicsComponent* graphics_;
};

