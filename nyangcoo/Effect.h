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

	void setEffectPos(int x, int y);		// 이펙트 위치 설정

	std::string EffectXmlFileName;
	int EffectId;

	// 아래 변수들은 xml에서 읽어온 값을 넣는다. 한 프레임의 이미지 크기, 프레임 갯수, 프레임당 시간.
	float frameWidth;		// 한 스프라이트 이미지 너비
	float frameHeight;		// 한 스프라이트 이미지 높이
	int frameNum;			// 프레임 수
	float frameDelta;		// 한 프레임 당 시간
	int spriteRowNum;		// 스프라이트 이미지 줄 갯수
	int imgNumPerLine;		// 스프라이트 한 줄 당 이미지 갯수

private:
	EffectGraphicsComponent* effectGraphics_;
};

