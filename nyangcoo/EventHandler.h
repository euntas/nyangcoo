#pragma once
class EventHandler
{
public:
	EventHandler();

	EventHandler& GetInstance();

	// ��Ŭ�� �̺�Ʈ �߻� �� 
	void OnLButtonDown(UINT nFlags, CPoint point, StaticObject* obj);

	// Btn ������ ��
	void OnBtnDown(Btn* btn);
};

