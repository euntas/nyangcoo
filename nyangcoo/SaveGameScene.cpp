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

	infoStaticObj.emplace_back(bg);

	// ���� ���� �ε�
	XmlManager::GetInstance().ParseSavedData();

	// ���� ��ư ����
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
		}

		SlotBtn[idx]->getAssetFileName().assign(st.begin(), st.end());
		SlotBtn[idx]->setImgRC(Rect(0, 0, 900, 118));
		SlotBtn[idx]->setViewRC(SlotBtn[idx]->getImgRC());
		SlotBtn[idx]->setX(260);
		SlotBtn[idx]->setY(48 + idx * 140);

		infoStaticObj.emplace_back(SlotBtn[idx]);
	}

	Btn* SaveGameBtn = new Btn(eSaveLoadBtn_Save, TEXT("saveload\\SaveGame_btn.png"), Rect(0, 0, 200, 163), Rect(0, 0, 200, 163), 1190, 484, 0);
	infoStaticObj.emplace_back(SaveGameBtn);

	Btn* BackTitleBtn = new Btn(eScene_ChapterSelect, TEXT("saveload\\back_chapter_btn.png"), Rect(0, 0, 200, 159), Rect(0, 0, 200, 159), 900, 484, 0);
	infoStaticObj.emplace_back(BackTitleBtn);

	Btn* DeleteGameBtn = new Btn(eScene_DeleteGame, TEXT("saveload\\DeleteGame_btn.png"), Rect(0, 0, 200, 163), Rect(0, 0, 200, 163), 30, 479, 0);
	infoStaticObj.emplace_back(DeleteGameBtn);

	// ��ư Ŭ���� ��Ÿ�� �׸� �����ÿ��� ��Ȱ��ȭ
	selectedImg = new StaticObject();
	selectedImg->setAssetFileName(TEXT("saveload\\Save_Cursor.png"));
	selectedImg->setImgRC(Rect(0, 0, 99, 87));
	selectedImg->setViewRC(selectedImg->getImgRC());
	selectedImg->setX(94);
	selectedImg->setY(64);
	selectedImg->setVisible(false);

	infoStaticObj.emplace_back(selectedImg);

	// ���� ���
	//XmlManager::GetInstance().ParseSavedData();
	for (auto& it : GameManager::GetInstance().slotList)
	{
		int lastStageNum;

		// ���Կ� ���� �����Ͱ� �ִٸ�
		if (it.second == true)
		{
			// ���� ������ �ر� �������� ��ȣ ��������
			lastStageNum = XmlManager::GetInstance().getLastStageNum(it.first);

			tempTitleStr[it.first] = GameManager::GetInstance().StageTitle[lastStageNum];
		}
		else
		{
			tempTitleStr[it.first] = L"����� �����Ͱ� �����ϴ�.";
		}
	}

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());
	popUp->setVisible(false);
	infoStaticObj.emplace_back(popUp);
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
		if (it == nullptr) continue;

		if (it->getObjtype() == eObjectType_PopUp)
		{
			PopUp* p = reinterpret_cast<PopUp*>(it);
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