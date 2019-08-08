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

	int curState;

	std::wstring PlayerAssetFileName[eState_Cnt];

	// �Ʒ� �������� xml���� �о�� ���� �ִ´�. �� �������� �̹��� ũ��, ������ ����, �����Ӵ� �ð�.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[eState_Cnt];
	float frameHeight[eState_Cnt];
	int frameNum[eState_Cnt];
	float frameDelta[eState_Cnt];
	int spriteRowNum[eState_Cnt];			// ��������Ʈ �̹��� �� ����
	int imgNumPerLine[eState_Cnt];			// ��������Ʈ �� �� �� �̹��� ����

private:
	PlayerGraphicsComponent* playerGraphics_;
};

