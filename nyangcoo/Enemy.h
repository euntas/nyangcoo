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

	bool CheckDestroy();

	void setEnemyPos(int x, int y);		// ĳ���� ��ġ ����
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

	// �Ʒ� �������� xml���� �о�� ���� �ִ´�. �� �������� �̹��� ũ��, ������ ����, �����Ӵ� �ð�.
	// ex) frameWidth[eState_Run] = 4
	float frameWidth[eState_Cnt];			// �� ��������Ʈ �̹��� �ʺ�
	float frameHeight[eState_Cnt];			// �� ��������Ʈ �̹��� ����
	int frameNum[eState_Cnt];				// ������ ��
	float frameDelta[eState_Cnt];			// �� ������ �� �ð�
	int spriteRowNum[eState_Cnt];			// ��������Ʈ �̹��� �� ����
	int imgNumPerLine[eState_Cnt];			// ��������Ʈ �� �� �� �̹��� ����

private:
	PlayerGraphicsComponent* enemyGraphics_;
};

