#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager& GameManager::GetInstance()
{
	static GameManager gm;
	return gm;
}
