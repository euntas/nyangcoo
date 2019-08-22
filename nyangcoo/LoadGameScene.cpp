#include "pch.h"
#include "LoadGameScene.h"

LoadGameScene::LoadGameScene() : Scene()
{
	Name = "Scene_LoadGame";

	Init();
}

void LoadGameScene::Init()
{
	infoStaticObj.clear();

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("load_bg.png");
	bg->ImgRC = Rect(0, 0, 1420, 672);
	bg->ViewRC = bg->ImgRC;

	infoStaticObj.emplace_back(bg);

	// 슬롯 정보 로드
	XmlManager::GetInstance().ParseSavedData();

	// 슬롯 버튼 생성
	for (int idx = 0; idx < 3; idx++)
	{
		SlotBtn[idx] = new Btn();
		if (idx == 0)
		{
			SlotBtn[idx]->ID = eSaveLoadBtn_Select0;
		}
		else if (idx == 1)
		{
			SlotBtn[idx]->ID = eSaveLoadBtn_Select1;
		}
		else if (idx == 2)
		{
			SlotBtn[idx]->ID = eSaveLoadBtn_Select2;
		}

		std::string st;
		if (GameManager::GetInstance().slotList[idx])
		{
			st = "saveload\\Slot_Saved.png";
		}
		else
		{
			st = "saveload\\Slot_Empty.png";
			SlotBtn[idx]->Enable = false;
		}
		
		SlotBtn[idx]->AssetFileName.assign(st.begin(), st.end());
		SlotBtn[idx]->ImgRC = Rect(0, 0, 900, 118);
		SlotBtn[idx]->ViewRC = SlotBtn[idx]->ImgRC;
		SlotBtn[idx]->x = 260;
		SlotBtn[idx]->y = 48 + idx*140;

		infoStaticObj.emplace_back(SlotBtn[idx]);
	}

	Btn* LoadGameBtn = new Btn();
	LoadGameBtn->ID = eSaveLoadBtn_Load;
	LoadGameBtn->AssetFileName = TEXT("saveload\\LoadGame_btn.png");
	LoadGameBtn->ImgRC = Rect(0, 0, 200, 163);
	LoadGameBtn->ViewRC = LoadGameBtn->ImgRC;
	LoadGameBtn->x = 1190;
	LoadGameBtn->y = 484;

	infoStaticObj.emplace_back(LoadGameBtn);

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	BackTitleBtn->AssetFileName = TEXT("saveload\\start_scene_btn.png");
	BackTitleBtn->ImgRC = Rect(0, 0, 200, 159);
	BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
	BackTitleBtn->x = 900;
	BackTitleBtn->y = 484;

	infoStaticObj.emplace_back(BackTitleBtn);

	Btn* DeleteGameBtn = new Btn();
	DeleteGameBtn->ID = eScene_DeleteGame;
	DeleteGameBtn->AssetFileName = TEXT("saveload\\DeleteGame_btn.png");
	DeleteGameBtn->ImgRC = Rect(0, 0, 200, 163);
	DeleteGameBtn->ViewRC = DeleteGameBtn->ImgRC;
	DeleteGameBtn->x = 30;
	DeleteGameBtn->y = 479;

	infoStaticObj.emplace_back(DeleteGameBtn);

	// 버튼 클릭시 나타날 그림 생성시에는 비활성화
	selectedImg = new StaticObject();
	selectedImg->AssetFileName = TEXT("saveload\\Save_Cursor.png");
	selectedImg->ImgRC = Rect(0, 0, 99, 87);
	selectedImg->ViewRC = selectedImg->ImgRC;
	selectedImg->x = 94;
	selectedImg->y = 64;
	selectedImg->Visible = false;

	infoStaticObj.emplace_back(selectedImg);

	GameManager::GetInstance().seletedSlotNum = -1;



	// 글자 출력
	for (auto& it : GameManager::GetInstance().slotList)
	{
		int lastStageNum;

		// 슬롯에 저장 데이터가 있다면
		if (it.second == true)
		{
			// 가장 마지막 해금 스테이지 번호 가져오기
			lastStageNum = XmlManager::GetInstance().getLastStageNum(it.first);

			tempTitleStr[it.first] = GameManager::GetInstance().StageTitle[lastStageNum];
		}
		else
		{
			tempTitleStr[it.first] = L"저장된 데이터가 없습니다.";
		}
	}

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->ImgRC = Rect(0, 0, 271, 279);
	popUp->ViewRC = popUp->ImgRC;
	popUp->Visible = false;
	infoStaticObj.emplace_back(popUp);
}

void LoadGameScene::Update(float Delta)
{
	int seletedSlotNum = GameManager::GetInstance().seletedSlotNum;

	if (seletedSlotNum != -1)
	{
		selectedImg->y = 48 + (seletedSlotNum * 140);
		selectedImg->Visible = true;
	}
	else
	{
		selectedImg->Visible = false;
	}

	Scene::Update(Delta);
}

void LoadGameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);

	for (int i = 0; i < 3; i++)
	{
		Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

		PointF P(450, 80 + i * 140);

		SolidBrush B(Color(0, 0, 0));

		pGraphics->DrawString(tempTitleStr[i].c_str(), -1, &F, P, &B);
	}

	for (auto& it : infoStaticObj)
	{
		if (it == nullptr) continue;

		if (it->Objtype == eObjectType_PopUp)
		{
			PopUp* p = reinterpret_cast<PopUp*>(it);
			if (p->name == ePopup_close)
			{
				p->Render(pGraphics);
			}
			
		}
	}
}

void LoadGameScene::Release()
{

}