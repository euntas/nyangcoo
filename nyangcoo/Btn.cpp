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
		//TODO. 추후 종료 확인 창을 띄우는 작업을 해야함.
		ExitProcess(0);
		break;
	}
}