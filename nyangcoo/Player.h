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

	// 아래 변수들은 xml에서 읽어온 값을 넣는다. 한 프레임의 이미지 크기, 프레임 갯수, 프레임당 시간.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[eState_Cnt];
	float frameHeight[eState_Cnt];
	int frameNum[eState_Cnt];
	float frameDelta[eState_Cnt];
	int spriteRowNum[eState_Cnt];			// 스프라이트 이미지 줄 갯수
	int imgNumPerLine[eState_Cnt];			// 스프라이트 한 줄 당 이미지 갯수

private:
	PlayerGraphicsComponent* playerGraphics_;
};

