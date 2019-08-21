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
	bool IsClicked; // save, load 위함
	int selectOption; // 선택지 선택 0 or 1 (선택없을 경우 -1)
};

