#pragma once
#include "GraphicsComponent.h"
class EffectGraphicsComponent :
	public GraphicsComponent
{
public:
	virtual void update(Object* obj, float Delta);
	virtual void render(Object* obj, Gdiplus::Graphics* pGraphics);

	void Init(float width, float height, int frameNum, float delta, int rownum, int imgNumPerLine); // TODO. 추후 xml 파일을 읽어서 초기화해주도록 바꾸어야 함

	void setAniUnitSize(float width, float height);
	void setAniFrameCnt(int frameNum);
	void setAniDelta(float delta);
	void InitAniUnits(int rownum, int imgNumPerLine);	// (애니메이션 용) 이미지에서 프레임 단위로 AniUnits에 그림 저장

private:
	float AniUnitWidth;		// (애니메이션 용) 한 프레임용 이미지 가로 길이
	float AniUnitHeight;	// (애니메이션 용) 한 프레임용 이미지 세로 길이
	int AniFrameSize;		// (애니메이션 용) 애니메이션 스프라이트 프레임 수

	int AniFrameCnt = 0;		// (애니메이션 용) 현재 애니메이션 스프라이트 프레임 번호

	float AniDelta;			// 애니메이션 한 프레임당 시간

	float EffectDeltaA;		// 전체 계산용 델타 변수

	std::vector<Gdiplus::Rect> AniUnits;
};

