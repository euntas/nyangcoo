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
		break;
	case eScene_Load:
		SceneManager::GetInstance().LoadScene(CString("Scene_LoadGame"));
		break;
	case eScene_Start:
		SceneManager::GetInstance().LoadScene(CString("Scene_Start"));
		break;
	case eScene_Exit:
		//PostQuitMessage(0);
		//TODO. ���� ���� Ȯ�� â�� ���� �۾��� �ؾ���.
		ExitProcess(0);
		break;
	}
}