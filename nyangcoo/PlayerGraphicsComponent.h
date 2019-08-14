#pragma once
#include "GraphicsComponent.h"
class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(Object* obj);
	PlayerGraphicsComponent(Player* obj);
	PlayerGraphicsComponent(Enemy* obj);

	virtual void update(float Delta);
	virtual void render(Gdiplus::Graphics* pGraphics);
	
	void Init();
	
	void InitAniUnits();	// (애니메이션 용) 이미지에서 프레임 단위로 AniUnits에 그림 저장

	void InitParams();

private:

	//float AniUnitWidth[eState_Cnt];		// (애니메이션 용) 한 프레임용 이미지 가로 길이
	//float AniUnitHeight[eState_Cnt];	// (애니메이션 용) 한 프레임용 이미지 세로 길이
	//int AniFrameSize[eState_Cnt];		// (애니메이션 용) 애니메이션 스프라이트 프레임 수

	int AniFrameCnt = 0;		// (애니메이션 용) 현재 애니메이션 스프라이트 프레임 번호

	//float AniDelta[eState_Cnt];			// 애니메이션 한 프레임당 시간

	float PlayerDeltaA;		// 전체 계산용 델타 변수

	//int curState;

	//std::vector<Gdiplus::Rect> AniUnits[eState_Cnt];
};

