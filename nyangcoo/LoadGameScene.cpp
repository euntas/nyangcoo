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
		Btn* SlotBtn = new Btn();
		if (idx == 0)
		{
			SlotBtn->ID = eSaveLoadBtn_Select0;
		}
		else if (idx == 1)
		{
			SlotBtn->ID = eSaveLoadBtn_Select1;
		}
		else if (idx == 2)
		{
			SlotBtn->ID = eSaveLoadBtn_Select2;
		}

		std::string st;
		if (GameManager::GetInstance().slotList[idx])
		{
			st = "test" + to_string(idx + 1) + "_check.png";
		}
		else
		{
			st = "test" + to_string(idx + 1) + ".png";
			SlotBtn->Enable = false;
		}
		
		SlotBtn->AssetFileName.assign(st.begin(), st.end());
		SlotBtn->ImgRC = Rect(0, 0, 520, 100);
		SlotBtn->ViewRC = SlotBtn->ImgRC;
		SlotBtn->x = 500;
		SlotBtn->y = 80 + idx*120;

		infoStaticObj.emplace_back(SlotBtn);
	}

	Btn* LoadGameBtn = new Btn();
	LoadGameBtn->ID = eSaveLoadBtn_Load;
	LoadGameBtn->AssetFileName = TEXT("load_btn.png");
	LoadGameBtn->ImgRC = Rect(0, 0, 200, 84);
	LoadGameBtn->ViewRC = LoadGameBtn->ImgRC;
	LoadGameBtn->x = 1200;
	LoadGameBtn->y = 526;

	infoStaticObj.emplace_back(LoadGameBtn);

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	BackTitleBtn->AssetFileName = TEXT("back_btn.png");
	BackTitleBtn->ImgRC = Rect(0, 0, 200, 84);
	BackTitleBtn->ViewRC = BackTitleBtn->ImgRC;
	BackTitleBtn->x = 900;
	BackTitleBtn->y = 526;

	infoStaticObj.emplace_back(BackTitleBtn);

	Btn* DeleteGameBtn = new Btn();
	DeleteGameBtn->ID = eScene_DeleteGame;
	DeleteGameBtn->AssetFileName = TEXT("delete_btn.png");
	DeleteGameBtn->ImgRC = Rect(0, 0, 200, 83);
	DeleteGameBtn->ViewRC = DeleteGameBtn->ImgRC;
	DeleteGameBtn->x = 20;
	DeleteGameBtn->y = 527;

	infoStaticObj.emplace_back(DeleteGameBtn);

	// 버튼 클릭시 나타날 그림 생성시에는 비활성화
	selectedImg = new StaticObject();
	selectedImg->AssetFileName = TEXT("btn_selected.png");
	selectedImg->ImgRC = Rect(0, 0, 154, 154);
	selectedImg->ViewRC = selectedImg->ImgRC;
	selectedImg->x = 100;
	selectedImg->y = 40;
	selectedImg->Visible = false;

	infoStaticObj.emplace_back(selectedImg);

	seletedSlotNum = -1;
}

void LoadGameScene::Update(float Delta)
{
	if (seletedSlotNum == 0 || seletedSlotNum == 1 || seletedSlotNum == 2)
	{
		selectedImg->y = 40 + (seletedSlotNum * 120);
		selectedImg->Visible = true;
	}

	Scene::Update(Delta);
}

void LoadGameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void LoadGameScene::Release()
{

}