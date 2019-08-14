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

	//void setAniUnitSize(float width, float height);
	//void setAniFrameCnt(int frameNum);
	//void setAniDelta(float delta);
	void InitAniUnits(int rownum, int imgNumPerLine);	// (애니메이션 용) 이미지에서 프레임 단위로 AniUnits에 그림 저장

private:
//	float AniUnitWidth;		// (애니메이션 용) 한 프레임용 이미지 가로 길이
	//float AniUnitHeight;	// (애니메이션 용) 한 프레임용 이미지 세로 길이
	//int AniFrameSize;		// (애니메이션 용) 애니메이션 스프라이트 프레임 수

	int AniFrameCnt = 0;		// (애니메이션 용) 현재 애니메이션 스프라이트 프레임 번호

	//float AniDelta;			// 애니메이션 한 프레임당 시간

	float EffectDeltaA;		// 전체 계산용 델타 변수

	std::vector<Gdiplus::Rect> AniUnits;
};

