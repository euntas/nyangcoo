#include "pch.h"
#include "EventHandler.h"

EventHandler::EventHandler()
{

}

EventHandler& EventHandler::GetInstance()
{
	static EventHandler eh;
	return eh;
}

void EventHandler::OnLButtonDown(UINT nFlags, CPoint point, StaticObject* obj)
{
	if (obj == nullptr) return;

	// Btn 오브젝트 클릭
	if (obj->getObjtype() == eObjectType_Btn && obj->getViewRC().Contains(point.x, point.y))
	{
		Btn* btn = reinterpret_cast<Btn*>(obj);
		OnBtnDown(btn);
	}
}

void EventHandler::OnBtnDown(Btn* btn)
{
	if (btn == nullptr) return;

	if (btn->getEnable() == false) return;

	switch (btn->getId())
	{
	default:
		break;
	}


}

