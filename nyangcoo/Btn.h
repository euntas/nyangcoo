#pragma once
#include "StaticObject.h"
class Btn : public StaticObject
{
public:
	Btn();
	Btn(int _stageID);

	Btn(
		int _id, 
		std::wstring _assetFileName, 
		Gdiplus::Rect _imgRC, 
		Gdiplus::Rect _viewRC, 
		int _x, 
		int _y,
		int _stageID = 0
	);

	void SendLButtonDown();
	int ID;
	int stageID;
	bool IsClicked; // save, load ����
	int selectOption; // ������ ���� 0 or 1 (���þ��� ��� -1)
};

