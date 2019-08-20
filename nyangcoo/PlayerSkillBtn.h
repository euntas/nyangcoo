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

	ESkillType skillType;
	std::string Name;

	StaticObject* btnImg;

	int CurID;

	float angle;
};

