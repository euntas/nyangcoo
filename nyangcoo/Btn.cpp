#include "pch.h"
#include "Btn.h"
#include <cstdlib>
#include <ctime>

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

Btn::Btn(int _id, std::wstring _assetFileName, Gdiplus::Rect _imgRC, Gdiplus::Rect _viewRC, int _x, int _y, int _stageID)
	: StaticObject(EObjectType::eObjectType_Btn)
{	
	stageID = _stageID;
	IsClicked = false;
	selectOption = -1;

	ID = _id;
	assetFileName = _assetFileName;
	imgRC = _imgRC;
	viewRC = _viewRC;
	x = _x;
	y = _y;
}

void Btn::SendLButtonDown()
{
	if (enable == false)
		return;

	switch (ID)
	{
	case eScene_Game: 
		sndPlaySound(NULL, SND_ASYNC);
		sndPlaySound(L"Asset\\BattleSound.wav", SND_ASYNC | SND_LOOP);
		GameManager::GetInstance().btnID = stageID;
		SceneManager::GetInstance().LoadScene(CString("Scene_Game"));
		SceneManager::GetInstance().Init();
		break;
	case eScene_LoadGame:
		SceneManager::GetInstance().LoadScene(CString("Scene_LoadGame"));
		SceneManager::GetInstance().Init();
		break;
	
	case eScene_Start:
		sndPlaySound(NULL, SND_ASYNC);
		sndPlaySound(L"Asset\\MainSound.wav", SND_ASYNC | SND_LOOP);
		SceneManager::GetInstance().LoadScene(CString("Scene_Start"));
		SceneManager::GetInstance().Init();
		break;
	
	case eScene_ChapterSelect:
	{
		sndPlaySound(NULL, SND_ASYNC);
		sndPlaySound(L"Asset\\MainSound.wav", SND_ASYNC | SND_LOOP);
		if (SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Start")
		{
			StartScene* ss = reinterpret_cast<StartScene*>(SceneManager::GetInstance().GetCurScene());
			for (auto& it : ss->getInfoStaticObj())
			{
				if (it->getObjtype() == eObjectType_Btn && it->getAssetFileName() == TEXT("title_btn_00.png"))
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
		else if (SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Script")
		{
			if (selectOption == 0 || selectOption == 1)
			{
				GameManager::GetInstance().stageSelectedList[GameManager::GetInstance().curStage->getStageID()] = selectOption;
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
			GameManager::GetInstance().InitCharacterSelectedList();
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

				// 슬롯에 저장 데이터가 있다면
				if (it.second == true)
				{
					// 가장 마지막 해금 스테이지 번호 가져오기
					lastStageNum = XmlManager::GetInstance().getLastStageNum(it.first);

					sgs->tempTitleStr[it.first] = GameManager::GetInstance().StageTitle[lastStageNum];
				}
				else
				{
					sgs->tempTitleStr[it.first] = L"저장된 데이터가 없습니다.";
				}
			}
		}

		SceneManager::GetInstance().LoadScene(CString("Scene_SaveGame"));
		SceneManager::GetInstance().Init();
		break;
	}
      
	case eScene_Help:
	{
		if (SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
		{
			for (auto& it : SceneManager::GetInstance().GetCurScene()->getInfoUIObj())
			{
				if (it->getObjtype() == eObjectType_None && it->getAssetFileName() == L"help_popup.png")
				{
					it->setVisible(!it->getVisible());
				}
			}
		}
		else
		{
			ExitProcess(0);
		}
    
		break;
	}

	case ePlayerUpgradeBtn:
	{
		GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

		int gdelta = 50 + (50 * GameManager::GetInstance().playerUpgradeLevel);
		int gcost = 100 * (GameManager::GetInstance().playerUpgradeLevel + 1);

		if (gs->gsGoldDelta - gdelta > 0 && GameManager::GetInstance().playerUpgradeLevel < 3 && gs->gold >= gcost)
		{
			gs->gold -= gcost;
			gs->gsGoldDelta -= gdelta;

			GameManager::GetInstance().playerUpgradeLevel++;
			gcost = 100 * (GameManager::GetInstance().playerUpgradeLevel + 1);
			std::wstring tempStr = L"slot\\up_slot_" + to_wstring(gcost) + L".png";

			this->setAssetFileName(tempStr);
		}
			
		break;
	}

	case eSuffleBtn:
	{
		CookieSelectScene* css = reinterpret_cast<CookieSelectScene*>(SceneManager::GetInstance().GetCurScene());

		std::string tempList[eCharacter_Cnt] = { "pistachio", "whitechoco", "muscle", "windarcher", "kiwi", "lemon", "moonrabit", "plum" };

		srand((unsigned int)time(NULL));
		for (int i = 0; i < MAX_SELECT_COOKIE_NUM; i++)
		{
			int num = rand() % eCharacter_Cnt;
			GameManager::GetInstance().characterSelectedList[i] = tempList[num];
		}

		css->Init();

		break;
	}
    
	case eScene_Exit:
			ExitProcess(0);
		
		break;
	}
}