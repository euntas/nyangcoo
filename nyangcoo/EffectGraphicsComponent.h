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
	void InitAniUnits(int rownum, int imgNumPerLine);	// (애니메이션 용) 이미지에서 프레임 단위로 AniUnits에 그림 저장

private:
	int AniFrameCnt = 0;	// (애니메이션 용) 현재 애니메이션 스프라이트 프레임 번호
	float EffectDeltaA;		// 전체 계산용 델타 변수

	std::vector<Gdiplus::Rect> AniUnits;
};

