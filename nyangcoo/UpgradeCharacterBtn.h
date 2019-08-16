#pragma once
#include "StaticObject.h"
class UpgradeCharacterBtn :
	public StaticObject
{
public:
	UpgradeCharacterBtn(MakeCharacterBtn* parent);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void SendLButtonDown();

	void printCost(Gdiplus::Graphics* pGraphics);

	MakeCharacterBtn* parentMakeBtn;

	int upgradeCost;
};

