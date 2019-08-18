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

	float gsGoldDelta;			// ��� ���� ���ؼӵ�
	float gsGoldDeltaA;

	StaticObject* goldBg;		// ���� ���
	StaticObject* goldPart[10];	// ���� ����

	Character* CommandPlayer;	// TODO. �������� �������� �����;� ��

	// TODO. ���߿� ������������ ���� �������� ���� ������ ������ ��.
	int maxGold = 1500;
};

