#pragma once
#include "Object.h"
class Player :
	public Object
{
public:
	Player();

	virtual void Init(InputComponent* input, PlayerGraphicsComponent* graphics);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	int x, y;

private:
	PlayerGraphicsComponent* playerGraphics_;
};

