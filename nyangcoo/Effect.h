#pragma once
#include "Object.h"

class Effect :
	public Object
{
public:
	Effect();

	virtual void Init(EffectGraphicsComponent* graphics);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void setEffectPos(int x, int y);		// ����Ʈ ��ġ ����

	std::string EffectXmlFileName;
	int EffectId;

	// �Ʒ� �������� xml���� �о�� ���� �ִ´�. �� �������� �̹��� ũ��, ������ ����, �����Ӵ� �ð�.
	float frameWidth;		// �� ��������Ʈ �̹��� �ʺ�
	float frameHeight;		// �� ��������Ʈ �̹��� ����
	int frameNum;			// ������ ��
	float frameDelta;		// �� ������ �� �ð�
	int spriteRowNum;		// ��������Ʈ �̹��� �� ����
	int imgNumPerLine;		// ��������Ʈ �� �� �� �̹��� ����

private:
	EffectGraphicsComponent* effectGraphics_;
};

