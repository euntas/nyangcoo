#include "pch.h"
#include "CookieSelectScene.h"

CookieSelectScene::CookieSelectScene() : Scene()
{
	Name = "Scene_CookieSelect";

	Init();
}

void CookieSelectScene::Init()
{
	infoStaticObj.clear();

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("CookieSelect_bg.png");
	bg->ImgRC = Rect(0, 0, 1420, 672);
	bg->ViewRC = bg->ImgRC;

	Btn* GameStartBtn = new Btn();
	GameStartBtn->ID = eScene_Game;
	GameStartBtn->AssetFileName = TEXT("SelectStart_btn.png");
	GameStartBtn->ImgRC = Rect(0, 0, 403, 118);
	GameStartBtn->ViewRC = GameStartBtn->ImgRC;
	GameStartBtn->x = 59;
	GameStartBtn->y = 534;

	Btn* RefreshBtn = new Btn();
	RefreshBtn->ID = eSuffleBtn;
	RefreshBtn->AssetFileName = TEXT("Refresh_btn.png");
	RefreshBtn->ImgRC = Rect(0, 0, 403, 118);
	RefreshBtn->ViewRC = RefreshBtn->ImgRC;
	RefreshBtn->x = 59;
	RefreshBtn->y = 408;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(GameStartBtn);
	infoStaticObj.emplace_back(RefreshBtn);

	for (int i = 0; i < MAX_SELECT_COOKIE_NUM; i++)
	{
		selectChar(GameManager::GetInstance().characterSelectedList[i], i);
	}

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->ImgRC = Rect(0, 0, 271, 279);
	popUp->ViewRC = popUp->ImgRC;
	popUp->Visible = false;
	infoStaticObj.emplace_back(popUp);
}

void CookieSelectScene::selectChar(std::string name, int placeIdx)
{
	std::string charFilename = "cookieSelect\\" + name + ".png";

	StaticObject* Selected = new StaticObject();
	Selected->Objtype = eObjectType_None;
	Selected->AssetFileName.assign(charFilename.begin(), charFilename.end());
	Selected->ImgRC = Rect(0, 0, 203, 220);
	Selected->ViewRC = Selected->ImgRC;
	Selected->x = 40 + placeIdx * 280;
	Selected->y = 40;

	infoStaticObj.emplace_back(Selected);
}

void CookieSelectScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void CookieSelectScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);

	printCoin(pGraphics);
	printCharacterText(pGraphics);
}

void CookieSelectScene::Release()
{

}

void CookieSelectScene::printCoin(Gdiplus::Graphics* pGraphics)
{
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(600, 500);
	PointF P2(600, 550);

	SolidBrush B(Color(0, 0, 0));

	int coin = GameManager::GetInstance().coin;
	int stageNum = GameManager::GetInstance().curStage->stageID;

	if (GameManager::GetInstance().seletedSlotNum != -1)
	{
		coin = GameManager::GetInstance().savedCoinList[GameManager::GetInstance().seletedSlotNum];
		stageNum = XmlManager::GetInstance().getLastStageNum(GameManager::GetInstance().seletedSlotNum);
	}

	wstring tempStr = L"현재 스테이지는 " + std::to_wstring(stageNum) + L" 입니다.";
	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);

	wstring tempStr2 = L"현재 소지한 냥코인은 " + std::to_wstring(coin) + L" 입니다.";
	pGraphics->DrawString(tempStr2.c_str(), -1, &F, P2, &B);
}

void CookieSelectScene::printCharacterText(Gdiplus::Graphics* pGraphics)
{
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	SolidBrush B(Color(0, 0, 0));

	for (int i = 0; i < MAX_SELECT_COOKIE_NUM; i++)
	{
		std::string name = GameManager::GetInstance().characterSelectedList[i];

		PointF P(40 + i * 280, 340);

		wstring tempStr;
		tempStr.assign(name.begin(), name.end());
		pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
	}
	
}