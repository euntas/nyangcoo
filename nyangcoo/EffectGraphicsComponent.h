#pragma once
#include "GraphicsComponent.h"
class EffectGraphicsComponent :
	public GraphicsComponent
{
public:
	EffectGraphicsComponent::EffectGraphicsComponent(Object* obj);
	EffectGraphicsComponent::EffectGraphicsComponent(Effect* obj);

	virtual void update(float Delta);
	virtual void render(Gdiplus::Graphics* pGraphics);

	void Init(); 
	void InitAniUnits(int rownum, int imgNumPerLine);	// (�ִϸ��̼� ��) �̹������� ������ ������ AniUnits�� �׸� ����

private:
	int AniFrameCnt = 0;	// (�ִϸ��̼� ��) ���� �ִϸ��̼� ��������Ʈ ������ ��ȣ
	float EffectDeltaA;		// ��ü ���� ��Ÿ ����

	std::vector<Gdiplus::Rect> AniUnits;
};

