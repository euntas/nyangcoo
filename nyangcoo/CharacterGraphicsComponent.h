#pragma once
#include "GraphicsComponent.h"
class CharacterGraphicsComponent : public GraphicsComponent
{
public:
	CharacterGraphicsComponent(Object* obj);
	CharacterGraphicsComponent(Character* obj);

	virtual void update(float Delta);
	virtual void render(Gdiplus::Graphics* pGraphics);
	
	void Init();
	
	void InitAniUnits();	// (�ִϸ��̼� ��) �̹������� ������ ������ AniUnits�� �׸� ����

	void InitParams();

private:
	int AniFrameCnt = 0;		// (�ִϸ��̼� ��) ���� �ִϸ��̼� ��������Ʈ ������ ��ȣ

	float PlayerDeltaA;		// ��ü ���� ��Ÿ ����
};

