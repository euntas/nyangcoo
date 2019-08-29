#include "pch.h"
#include "EventHandler.h"

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{

}

EventHandler& EventHandler::GetInstance()
{
	static EventHandler eh;
	return eh;
}

void EventHandler::AddEvent(std::function<void(void)> func, EEvent _event)
{
	dicEvent[_event].emplace_back(func);
}

void EventHandler::OnEvent(EEvent _event)
{
	for (auto& it : dicEvent[_event])
	{
		it();
	}
}

