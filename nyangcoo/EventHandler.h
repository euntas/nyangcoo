#pragma once
class EventHandler
{
public:
	EventHandler();

	EventHandler& GetInstance();

	// 왼클릭 이벤트 발생 시 
	void OnLButtonDown(UINT nFlags, CPoint point, StaticObject* obj);

	// Btn 눌렸을 때
	void OnBtnDown(Btn* btn);
};

