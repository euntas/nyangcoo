#pragma once
#include "GraphicsComponent.h"
class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	virtual void update(Object& obj, Gdiplus::Graphics& graphics, float Delta);
};

