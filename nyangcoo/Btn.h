#pragma once
#include "StaticObject.h"
class Btn : public StaticObject
{
public:
	Btn();
	Btn(int _stageID);

	void SendLButtonDown();
	int ID;
	int stageID;
	bool IsClicked; // save, load ����
	int selectOption; // ������ ���� 0 or 1 (���þ��� ��� -1)
};

