#pragma once
#include "StaticObject.h"
class PlayerSkillBtn :
	public StaticObject
{
public:
	PlayerSkillBtn();
	PlayerSkillBtn(std::string skillName);

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void SendLButtonDown();

	StaticObject* btnImg;
	Effect* skillEffect;

	int CurID;
};

