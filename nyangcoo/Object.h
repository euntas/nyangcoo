#pragma once

class Object
{
public:
	Object();
	Object(EObjectType InType);

	virtual void Init(InputComponent* input, GraphicsComponent* graphics);
	virtual void Update(Gdiplus::Graphics* graphics, float Delta);
	virtual void Release();

	std::wstring AssetFileName;
	Gdiplus::Rect rc;
	EObjectType Objtype;
	bool Enable;

private:
	InputComponent* input_;
	GraphicsComponent* graphics_;
};

