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

	// 아래 변수들은 xml에서 읽어온 값을 넣는다. 한 프레임의 이미지 크기, 프레임 갯수, 프레임당 시간.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[4];
	float frameHeight[4];
	int frameNum[4]; 
	float frameDelta[4];

private:
	PlayerGraphicsComponent* playerGraphics_;
};

