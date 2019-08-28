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

	// Getter, Setter
	int getId();
	void setId(int _id);

	int getStageId();
	void setStageId(int _stageId);

	bool getIsClicked();
	void setIsClicked(bool _isClicked);

	int getSelectOption();
	void setSelectOption(int _selectOption);

private:
	int id;
	int stageId;
	bool isClicked; // save, load 위함
	int selectOption; // 선택지 선택 0 or 1 (선택없을 경우 -1)
};

