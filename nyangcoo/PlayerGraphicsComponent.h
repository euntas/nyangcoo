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
	
	void InitAniUnits();	// (�ִϸ��̼� ��) �̹������� ������ ������ AniUnits�� �׸� ����

	void InitParams();

private:

	//float AniUnitWidth[eState_Cnt];		// (�ִϸ��̼� ��) �� �����ӿ� �̹��� ���� ����
	//float AniUnitHeight[eState_Cnt];	// (�ִϸ��̼� ��) �� �����ӿ� �̹��� ���� ����
	//int AniFrameSize[eState_Cnt];		// (�ִϸ��̼� ��) �ִϸ��̼� ��������Ʈ ������ ��

	int AniFrameCnt = 0;		// (�ִϸ��̼� ��) ���� �ִϸ��̼� ��������Ʈ ������ ��ȣ

	//float AniDelta[eState_Cnt];			// �ִϸ��̼� �� �����Ӵ� �ð�

	float PlayerDeltaA;		// ��ü ���� ��Ÿ ����

	//int curState;

	//std::vector<Gdiplus::Rect> AniUnits[eState_Cnt];
};

