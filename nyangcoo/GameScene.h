#pragma once
#include "Scene.h"

class GameScene :
	public Scene
{
public:
	GameScene();

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void printGold(int _gold, Gdiplus::Graphics* pGraphics);
	void InitGoldBar();
	void printTitle(Gdiplus::Graphics* pGraphics);
	void printHP(Character* _character, Gdiplus::Graphics* pGraphics);

	StaticObject* bg;

	int gold;

	float gsGoldDelta;			// 골드 증가 기준속도
	float gsGoldDeltaA;

	StaticObject* goldBg;		// 골드바 배경
	StaticObject* goldPart[10];	// 골드바 유닛

	Character* CommandPlayer;	// TODO. 스테이지 정보에서 가져와야 함

	// TODO. 나중에 스테이지에서 정보 가져오고 여기 변수는 지워야 함.
	int maxGold = 1500;
};

