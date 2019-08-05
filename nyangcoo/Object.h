#pragma once
#include "framework.h"

class Object
{
public:
	Object();
	Object(EObjectType InType);

	virtual void Begin() {}
	virtual void Update(float Delta) {}
	virtual void End() {}

	Gdiplus::Image* ParentImg;
	Gdiplus::Image* Img;
	Gdiplus::Rect rc;
	EObjectType Objtype;
	bool Enable;
};

