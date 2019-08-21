#include "pch.h"
#include "Btn.h"

Btn::Btn()
	: StaticObject(EObjectType::eObjectType_Btn)
{
	stageID = 0;
}

Btn::Btn(int _stageID)
	: StaticObject(EObjectType::eObjectType_Btn)
{
	stageID = _stageID;
}

void Btn::SendLButtonDown()
{
	if (Enable == false)
		return;

	switch (ID)
	{
	case eScene_Game: 
		GameManager::GetInstance().btnID = stageID;
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
	
	case eSaveLoadBtn_Select0:
	case eSaveLoadBtn_Select1:
	case eSaveLoadBtn_Select2:
	{
		LoadGameScene* lgs = reinterpret_cast<LoadGameScene*>(SceneManager::GetInstance().GetCurScene());
			
		if (this->ID == eSaveLoadBtn_Select0)
			lgs->seletedSlotNum = 0;
		else if (this->ID == eSaveLoadBtn_Select1)
			lgs->seletedSlotNum = 1;
		else if (this->ID == eSaveLoadBtn_Select2)
			lgs->seletedSlotNum = 2;

		break;
	}

	case eSaveLoadBtn_Load:
	{
		LoadGameScene* lgs = reinterpret_cast<LoadGameScene*>(SceneManager::GetInstance().GetCurScene());

		XmlManager::GetInstance().LoadSlotData(lgs->seletedSlotNum);

		SceneManager::GetInstance().LoadScene(CString("Scene_ChapterSelect"));
		SceneManager::GetInstance().Init();
		break;
	}
	
	case eScene_Exit:
			ExitProcess(0);
		
		break;
	}
}