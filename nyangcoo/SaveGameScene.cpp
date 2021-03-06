#include "pch.h"
#include "SaveGameScene.h"

SaveGameScene::SaveGameScene() : Scene()
{
	name = "Scene_SaveGame";

	Init();
}

void SaveGameScene::Init()
{
	infoStaticObj.clear();

	GameManager::GetInstance().seletedSlotNum = -1;

	bg = new StaticObject();
	bg->setObjtype(eObjectType_BGImage);
	bg->setAssetFileName(TEXT("load_bg.png"));
	bg->setImgRC(Rect(0, 0, 1420, 672));
	bg->setViewRC(bg->getImgRC());

	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_Background, bg));

	// 슬롯 정보 로드
	XmlManager::GetInstance().ParseSavedData();

	// 슬롯 버튼 생성
	for (int idx = 0; idx < 3; idx++)
	{
		SlotBtn[idx] = new Btn();
		if (idx == 0)
		{
			SlotBtn[idx]->setId(eSaveLoadBtn_Select0);
		}
		else if (idx == 1)
		{
			SlotBtn[idx]->setId(eSaveLoadBtn_Select1);
		}
		else if (idx == 2)
		{
			SlotBtn[idx]->setId(eSaveLoadBtn_Select2);
		}

		std::string st;
		if (GameManager::GetInstance().slotList[idx])
		{
			st = "saveload\\Slot_Saved.png";
		}
		else
		{
			st = "saveload\\Slot_Empty.png";
		}

		std::wstring tempFileName(st.begin(), st.end());
		SlotBtn[idx]->setAssetFileName(tempFileName);
		SlotBtn[idx]->setImgRC(Rect(0, 0, 900, 118));
		SlotBtn[idx]->setViewRC(SlotBtn[idx]->getImgRC());
		SlotBtn[idx]->setX(260);
		SlotBtn[idx]->setY(48 + idx * 140);

		infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, SlotBtn[idx]));
	}

	Btn* SaveGameBtn = new Btn(eSaveLoadBtn_Save, TEXT("saveload\\SaveGame_btn.png"), Rect(0, 0, 200, 163), Rect(0, 0, 200, 163), 1190, 484, 0);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, SaveGameBtn));

	Btn* BackTitleBtn = new Btn(eScene_ChapterSelect, TEXT("saveload\\back_chapter_btn.png"), Rect(0, 0, 200, 159), Rect(0, 0, 200, 159), 900, 484, 0);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, BackTitleBtn));

	Btn* DeleteGameBtn = new Btn(eScene_DeleteGame, TEXT("saveload\\DeleteGame_btn.png"), Rect(0, 0, 200, 163), Rect(0, 0, 200, 163), 30, 479, 0);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, DeleteGameBtn));

	// 버튼 클릭시 나타날 그림 생성시에는 비활성화
	selectedImg = new StaticObject();
	selectedImg->setAssetFileName(TEXT("saveload\\Save_Cursor.png"));
	selectedImg->setImgRC(Rect(0, 0, 99, 87));
	selectedImg->setViewRC(selectedImg->getImgRC());
	selectedImg->setX(94);
	selectedImg->setY(64);
	selectedImg->setVisible(false);

	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, selectedImg));

	// 글자 출력
	//XmlManager::GetInstance().ParseSavedData();
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
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());
	popUp->setVisible(false);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_Popup, popUp));
}

void SaveGameScene::Update(float Delta)
{
	int seletedSlotNum = GameManager::GetInstance().seletedSlotNum;

	if (seletedSlotNum != -1)
	{
		selectedImg->setY(48 + (seletedSlotNum * 140));
		selectedImg->setVisible(true);
	}
	else
	{
		selectedImg->setVisible(false);
	}

	Scene::Update(Delta);
}

void SaveGameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);

	for (int i=0; i<3; i++)
	{	
		Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

		PointF P(450, 80 + i * 140);

		SolidBrush B(Color(0, 0, 0));

		pGraphics->DrawString(tempTitleStr[i].c_str(), -1, &F, P, &B);
	}
	
	for (auto& it : infoStaticObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if (obj->getObjtype() == eObjectType_PopUp)
		{
			PopUp* p = reinterpret_cast<PopUp*>(obj);
			if (p->name == ePopup_close)
			{
				p->Render(pGraphics);
			}

		}
	}
}

void SaveGameScene::Release()
{

}