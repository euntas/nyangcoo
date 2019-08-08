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

	std::wstring PlayerAssetFileName[4];

	// �Ʒ� �������� xml���� �о�� ���� �ִ´�. �� �������� �̹��� ũ��, ������ ����, �����Ӵ� �ð�.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[4];
	float frameHeight[4];
	int frameNum[4]; 
	float frameDelta[4];

private:
	PlayerGraphicsComponent* playerGraphics_;
};

