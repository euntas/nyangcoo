#include "pch.h"
#include "Btn.h"

Btn::Btn()
	: StaticObject(EObjectType::eObjectType_Btn)
{
	stageID = 0;
	IsClicked = false;
	selectOption = -1;
}

Btn::Btn(int _stageID)
	: StaticObject(EObjectType::eObjectType_Btn)
{
	stageID = _stageID;
	IsClicked = false;
	selectOption = -1;
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
	{
		if (SceneManager::GetInstance().GetCurScene()->Name == "Scene_Start")
		{
			StartScene* ss = reinterpret_cast<StartScene*>(SceneManager::GetInstance().GetCurScene());
			for (auto& it : ss->infoStaticObj)
			{
				if (it->Objtype == eObjectType_Btn && it->AssetFileName == TEXT("title_btn_00.png"))
				{
					Btn* sb = reinterpret_cast<Btn*>(it);
					sb->IsClicked = !sb->IsClicked;

					if (sb->IsClicked)
					{
						GameManager::GetInstance().Init(0);
						break;
					}
				}
			}
		}
		else if (SceneManager::GetInstance().GetCurScene()->Name == "Scene_Script")
		{
			if (selectOption == 0 || selectOption == 1)
			{
				GameManager::GetInstance().stageSelectedList[GameManager::GetInstance().curStage->stageID] = selectOption;
			}
		}

		SceneManager::GetInstance().LoadScene(CString("Scene_ChapterSelect"));
		SceneManager::GetInstance().Init();
		break;
	}
	
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
		
		IsClicked = !IsClicked;

		if (this->ID == eSaveLoadBtn_Select0 && IsClicked)
		{
			GameManager::GetInstance().seletedSlotNum = 0;
		}
		else if (this->ID == eSaveLoadBtn_Select1 && IsClicked)
		{
			GameManager::GetInstance().seletedSlotNum = 1;
		}
		else if (this->ID == eSaveLoadBtn_Select2 && IsClicked)
		{
			GameManager::GetInstance().seletedSlotNum = 2;
		}
		else
		{
			GameManager::GetInstance().seletedSlotNum = -1;
		}

		break;
	}

	case eSaveLoadBtn_Load:
	{
		if (GameManager::GetInstance().seletedSlotNum != -1)
		{
			XmlManager::GetInstance().LoadSlotData(GameManager::GetInstance().seletedSlotNum);
		}

		SceneManager::GetInstance().LoadScene(CString("Scene_ChapterSelect"));
		SceneManager::GetInstance().Init();
		break;
	}

	case eSaveLoadBtn_Save:
	{
		if (GameManager::GetInstance().seletedSlotNum != -1)
		{
			XmlManager::GetInstance().SaveSlotData(GameManager::GetInstance().seletedSlotNum);
			XmlManager::GetInstance().ParseSavedData();
		}

		SceneManager::GetInstance().LoadScene(CString("Scene_SaveGame"));
		SceneManager::GetInstance().Init();
		break;
  }

	case eScene_DeleteGame:
	{
		SaveGameScene* sgs = reinterpret_cast<SaveGameScene*>(SceneManager::GetInstance().GetCurScene());

		if (GameManager::GetInstance().seletedSlotNum != -1)
		{
			XmlManager::GetInstance().DeleteSlotData(GameManager::GetInstance().seletedSlotNum);
			XmlManager::GetInstance().ParseSavedData();

			for (auto& it : GameManager::GetInstance().slotList)
			{
				int lastStageNum;

				// ���Կ� ���� �����Ͱ� �ִٸ�
				if (it.second == true)
				{
					// ���� ������ �ر� �������� ��ȣ ��������
					lastStageNum = XmlManager::GetInstance().getLastStageNum(it.first);

					sgs->tempTitleStr[it.first] = GameManager::GetInstance().StageTitle[lastStageNum];
				}
				else
				{
					sgs->tempTitleStr[it.first] = L"����� �����Ͱ� �����ϴ�.";
				}
			}
		}

		SceneManager::GetInstance().LoadScene(CString("Scene_SaveGame"));
		SceneManager::GetInstance().Init();
		break;
	}
      
	case eScene_Help:
  {
		if (SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
		{
			for (auto& it : SceneManager::GetInstance().GetCurScene()->infoUIObj)
			{
				if (it->Objtype == eObjectType_None && it->AssetFileName == L"help_popup.png")
				{
					it->Visible = !it->Visible;
				}
			}
		}
		else
		{
			ExitProcess(0);
		}
    
    break;
  }
    
	case eScene_Exit:
			ExitProcess(0);
		
		break;
	}
}