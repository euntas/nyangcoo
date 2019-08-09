#pragma once
#include "GraphicsComponent.h"
class EffectGraphicsComponent :
	public GraphicsComponent
{
public:
	virtual void update(Object* obj, float Delta);
	virtual void render(Object* obj, Gdiplus::Graphics* pGraphics);

	void Init(float width, float height, int frameNum, float delta, int rownum, int imgNumPerLine); // TODO. ���� xml ������ �о �ʱ�ȭ���ֵ��� �ٲپ�� ��

	void setAniUnitSize(float width, float height);
	void setAniFrameCnt(int frameNum);
	void setAniDelta(float delta);
	void InitAniUnits(int rownum, int imgNumPerLine);	// (�ִϸ��̼� ��) �̹������� ������ ������ AniUnits�� �׸� ����

private:
	float AniUnitWidth;		// (�ִϸ��̼� ��) �� �����ӿ� �̹��� ���� ����
	float AniUnitHeight;	// (�ִϸ��̼� ��) �� �����ӿ� �̹��� ���� ����
	int AniFrameSize;		// (�ִϸ��̼� ��) �ִϸ��̼� ��������Ʈ ������ ��

	int AniFrameCnt = 0;		// (�ִϸ��̼� ��) ���� �ִϸ��̼� ��������Ʈ ������ ��ȣ

	float AniDelta;			// �ִϸ��̼� �� �����Ӵ� �ð�

	float EffectDeltaA;		// ��ü ���� ��Ÿ ����

	std::vector<Gdiplus::Rect> AniUnits;
};

