#pragma once
#include "StaticObject.h"
class MakeCharacterBtn :
	public StaticObject
{
public:
	MakeCharacterBtn();
	MakeCharacterBtn(std::string characterName);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void SendLButtonDown();

	Character* MakeCharacter();

	StaticObject* makeSlotImg;
	StaticObject* characterImg;

	int cost;

	int CurStageID;

	ECharacter ID;
	std::string NameStr;

	int atk;
	int HP;

	bool IsReady;
};

