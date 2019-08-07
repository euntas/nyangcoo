#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(Object* obj, float Delta) = 0;
	virtual void render(Object* obj, Gdiplus::Graphics* pGraphics) = 0;
};

