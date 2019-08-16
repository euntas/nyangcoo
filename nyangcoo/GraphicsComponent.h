#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(float Delta) = 0;
	virtual void render(Gdiplus::Graphics* pGraphics) = 0;

protected:
	Object* parentObj;
};

