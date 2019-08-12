#include "pch.h"
#include "Btn.h"

Btn::Btn()
	: StaticObject(EObjectType::eObjectType_Btn)
{

}

void Btn::SendLButtonDown()
{
	switch (ID)
	{
	case eScene_Game: 
		SceneManager::GetInstance().LoadScene(CString("Scene_Game"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_LoadGame:
		SceneManager::GetInstance().LoadScene(CString("Scene_LoadGame"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_Start:
		SceneManager::GetInstance().LoadScene(CString("Scene_Start"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_ChapterSelect:
		SceneManager::GetInstance().LoadScene(CString("Scene_ChapterSelect"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_Exit:
		//PostQuitMessage(0);
		//TODO. ���� ���� Ȯ�� â�� ���� �۾��� �ؾ���.
		ExitProcess(0);
		break;
	}
}