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
	case eScene_CookieSelect:
		SceneManager::GetInstance().LoadScene(CString("Scene_CookieSelect"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_Script:
		SceneManager::GetInstance().LoadScene(CString("Scene_Script"));
		SceneManager::GetInstance().Init();

		break;
	case eScene_Exit:
		//PostQuitMessage(0);
		//TODO. 추후 종료 확인 창을 띄우는 작업을 해야함.
		/*if (SceneManager::GetInstance().GetCurScene()->Name == "Scene_Start")
		{
			for (auto& it : SceneManager::GetInstance().GetCurScene()->infoStaticObj)
			{
				if (it->Objtype == eObjectType_PopUp)
				{
					it->Visible = true;
				}
			}
			break;
		}
		else 
		{*/
			ExitProcess(0);
		//}
		
		break;
	}
}