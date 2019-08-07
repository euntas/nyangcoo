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

	std::wstring AssetFileName;
	Gdiplus::Rect rc;
	EObjectType Objtype;
	bool Enable;

protected:
	InputComponent* input_;
	GraphicsComponent* graphics_;
};

