#pragma once
#include "Object.h"
class Enemy :
	public Object
{
public:
	Enemy();

	virtual void Init();
	virtual void Init(InputComponent* input, PlayerGraphicsComponent* graphics);
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void setEnemyPos(int x, int y);		// 캐릭터 위치 설정
	void changeState(EState state);

	int curState;

	string name;

	float speed;

	float DeltaA;

	int atk;
	float atkSpeed;
	float atkDist;

	int hp;
	int gold;

	std::wstring EnemyAssetFileName[eState_Cnt];
	std::string EnemyXmlFileName;

	// 아래 변수들은 xml에서 읽어온 값을 넣는다. 한 프레임의 이미지 크기, 프레임 갯수, 프레임당 시간.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[eState_Cnt];			// 한 스프라이트 이미지 너비
	float frameHeight[eState_Cnt];			// 한 스프라이트 이미지 높이
	int frameNum[eState_Cnt];				// 프레임 수
	float frameDelta[eState_Cnt];			// 한 프레임 당 시간
	int spriteRowNum[eState_Cnt];			// 스프라이트 이미지 줄 갯수
	int imgNumPerLine[eState_Cnt];			// 스프라이트 한 줄 당 이미지 갯수

private:
	PlayerGraphicsComponent* enemyGraphics_;
};

