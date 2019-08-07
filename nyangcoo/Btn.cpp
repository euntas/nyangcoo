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
	case eScene_Exit:
		//PostQuitMessage(0);
		//TODO. ���� ���� Ȯ�� â�� ���� �۾��� �ؾ���.
		ExitProcess(0);
		break;
	}
}