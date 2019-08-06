#pragma once

class StaticObject
{
public:
	StaticObject();
	StaticObject(EObjectType InType);

	virtual void Init() {};
	virtual void Update(float Delta) {};
	virtual void Release() {};

	std::wstring AssetFileName;
	Gdiplus::Rect rc;
	EObjectType Objtype;
	bool Enable;
};

