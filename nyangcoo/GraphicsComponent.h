#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(Object* obj, Gdiplus::Graphics* graphics, float Delta) = 0;
};

