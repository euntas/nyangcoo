#pragma once
#include "GraphicsComponent.h"
class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(Object* obj);
	PlayerGraphicsComponent(Character* obj);

	virtual void update(float Delta);
	virtual void render(Gdiplus::Graphics* pGraphics);
	
	void Init();
	
	void InitAniUnits();	// (�ִϸ��̼� ��) �̹������� ������ ������ AniUnits�� �׸� ����

	void InitParams();

private:
	int AniFrameCnt = 0;		// (�ִϸ��̼� ��) ���� �ִϸ��̼� ��������Ʈ ������ ��ȣ

	float PlayerDeltaA;		// ��ü ���� ��Ÿ ����
};

