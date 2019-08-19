#include "pch.h"
#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	Init();
}

void GameScene::Init()
{
	// 초기 수치 부여
	ClearAll();

	gsGoldDeltaA = 0;
	gold = 1000;
	gsGoldDelta = 500; // 골드 증가 초기 속도

	// 게임 매니저 초기화
	GameManager::GetInstance().Init(GameManager::GetInstance().btnID);

	maxGold = GameManager::GetInstance().curStage->maxGold;

	// 배경 그림 깔기
	bg = GameManager::GetInstance().curStage->bg;
	infoStaticObj.emplace_back(bg);

	// 캐릭터 생성용 슬롯 버튼 만들기
	std::string charNameList[8] = { "pistachio",  "whitechoco", "muscle", "kiwi", "windarcher", "pistachio", "plum", "moonrabit" };
	MakeCharacterBtn* mcb[8];
	UpgradeCharacterBtn* ucb[8];

	for (int n = 0; n < 8; n++)
	{
		mcb[n] = new MakeCharacterBtn(charNameList[n]);
		if (n > 0)
			mcb[n]->x = mcb[n-1]->x + 100;
		infoStaticObj.emplace_back(mcb[n]);

		ucb[n] = new UpgradeCharacterBtn(mcb[n]);
		if (n > 0)
			ucb[n]->x = ucb[n - 1]->x + 100;
		infoStaticObj.emplace_back(ucb[n]);
	}
	
	// 플레이어 생성
	CommandPlayer = GameManager::GetInstance().CommandPlayer;
	infoObj.emplace_back(GameManager::GetInstance().CommandPlayer);

	// 적 생성
	for (auto& it : GameManager::GetInstance().curEnemyList)
	{
		infoObj.emplace_back(it);
	}

	// TODO. 나중에 수정필요. 팝업 부분
	PopUp* popUp = new PopUp(ePopup_close);

	//PopUp = new StaticObject();
	//popUp->Objtype = eObjectType_PopUp;
	//popUp->AssetFileName = TEXT("popup_all.png");
	popUp->Visible = false;
	popUp->ImgRC = Rect(0, 0, 250, 198);
	popUp->ViewRC = popUp->ImgRC;

	infoStaticObj.emplace_back(popUp);

	// TODO. 나중에 지우기
	Btn* ExitBtn = new Btn();
	ExitBtn->ID = eScene_Exit;
	ExitBtn->AssetFileName = TEXT("title_btn_04.png");
	ExitBtn->ImgRC = Rect(0, 0, 236, 72);
	ExitBtn->ViewRC = ExitBtn->ImgRC;
	ExitBtn->x = 1200;
	ExitBtn->y = 5;

	infoStaticObj.emplace_back(ExitBtn);

	Btn* LoadGameBtn = new Btn();
	LoadGameBtn->ID = eScene_LoadGame;
	LoadGameBtn->AssetFileName = TEXT("title_btn_02.png");
	LoadGameBtn->ImgRC = Rect(0, 0, 236, 72);
	LoadGameBtn->ViewRC = LoadGameBtn->ImgRC;
	LoadGameBtn->x = 1200;
	LoadGameBtn->y = 100;

	infoStaticObj.emplace_back(LoadGameBtn);

	// 골드 바
	InitGoldBar();

	ResultPopUp = new PopUp(ePopup_result);

	infoStaticObj.emplace_back(ResultPopUp);

}

void GameScene::InitGoldBar()
{
	goldBg = new StaticObject();
	goldBg->AssetFileName = TEXT("goldbar\\goldbar_bg.png");
	goldBg->ImgRC = Rect(0, 0, 414, 102);
	goldBg->ViewRC = goldBg->ImgRC;
	goldBg->x = 10;
	goldBg->y = 10;

	infoStaticObj.emplace_back(goldBg);

	for (int i = 0; i < 10; i++)
	{
		goldPart[i] = new StaticObject();
		goldPart[i]->AssetFileName = TEXT("goldbar\\goldbar_unit_brown.png");
		goldPart[i]->ImgRC = Rect(0, 0, 36, 64);
		goldPart[i]->ViewRC = goldPart[i]->ImgRC;
		if (i == 0)
		{
			goldPart[i]->x = goldBg->x + 25;
			goldPart[i]->y = goldBg->y + 19;
		}
		else
		{
			goldPart[i]->x = goldPart[i - 1]->x + 36;
			goldPart[i]->y = goldPart[i - 1]->y;
		}

		infoStaticObj.emplace_back(goldPart[i]);
	}
}

void GameScene::Update(float Delta)
{
	infoObj;
	// 게임이 종료되면 씬 전환
	if (GameManager::GetInstance().IsGameEnd())
	{
		Delta = 0;
		GameManager::GetInstance().IsGrayScale = true;
		
		if (GameManager::GetInstance().IsWin == false)
		{
			ResultPopUp->bg->AssetFileName = TEXT("result_lose.png");
		}
		else
		{
			GameManager::GetInstance().stageClearList[GameManager::GetInstance().curStage->stageID + 1] = true;
		}
		ResultPopUp->Visible = true;
	}

	Scene::Update(Delta);

	// 골드 관련 코드
	gsGoldDeltaA += Delta;

	if (gsGoldDeltaA > gsGoldDelta)
	{
		gsGoldDeltaA = 0;

		// max보다 작으면 골드 증가시킴
		
		if (gold < maxGold)
		{
			gold += 10;
		}	
	}

	// 골드바 출력위해 계산
	int goldPerUnit = maxGold / 10;
	int lastUnitNum = gold / goldPerUnit;

	for (int i = 0; i < 10; i++)
	{
		if (i < lastUnitNum)
			goldPart[i]->AssetFileName = TEXT("goldbar\\goldbar_unit_yellow.png");
		else
			goldPart[i]->AssetFileName = TEXT("goldbar\\goldbar_unit_brown.png");
	}

	// 죽은애들 처리
/*
	for (Object* ch : infoObj)
	{
		if (ch->Objtype == eObjectType_Effect)
		{
			Effect* e = reinterpret_cast<Effect*>(ch);
			if (e->Enable == false && e->Visible == false)
			{
				e = nullptr;
			}
		}
		else if (ch->Objtype == eObjectType_Character)
		{
			Character* c = reinterpret_cast<Character*>(ch);
			if (c->Enable == false && c->Visible == false)
			{
				ch = nullptr;
			}
		}
		
	}*/

	// wave관련 코드
	if (GameManager::GetInstance().IsAllEnemyDead())
	{
		if (GameManager::GetInstance().ChangeWave())
		{
			for (auto& it : GameManager::GetInstance().curEnemyList)
			{
				infoObj.emplace_back(it);
			}
		}
	}

}

void GameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);

	printTitle(pGraphics);
	printGold(gold, pGraphics);
	printHP(CommandPlayer, pGraphics);
}

void GameScene::Release()
{
	Scene::Release();
}

void GameScene::printGold(int _gold, Graphics* pGraphics)
{
	// 아이콘이미지 출력
	StaticObject* ic = new StaticObject();
	ic->Objtype = eObjectType_None;
	ic->AssetFileName = TEXT("goldbar\\gold_icon.png");
	ic->ImgRC = Rect(0, 0, 40, 39);
	ic->ViewRC = Rect(0, 0, 40, 39);
	ic->ViewRC.X = goldBg->x + 100;
	ic->ViewRC.Y = goldBg->y + 34;

	auto pImg = (AssetManager::GetInstance().GetImage(ic->AssetFileName)).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
	{
		//gray scale conversion:
		Gdiplus::ColorMatrix matrix =
		{
			.3f, .3f, .3f,   0,   0,
			.6f, .6f, .6f,   0,   0,
			.1f, .1f, .1f,   0,   0,
			0,   0,   0,   1,   0,
			0,   0,   0,   0,   1
		};

		Gdiplus::ImageAttributes attr;
		attr.SetColorMatrix(&matrix,
			Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		pGraphics->DrawImage(pImg.get(), ic->ViewRC, ic->ImgRC.X, ic->ImgRC.Y, ic->ImgRC.Width, ic->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), ic->ViewRC, ic->ImgRC.X, ic->ImgRC.Y, ic->ImgRC.Width, ic->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 글자 출력
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(goldBg->x + 130.0f, goldBg->y + 29.0f);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = std::to_wstring(_gold) + L"/" + std::to_wstring(maxGold);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printHP(Character* _character, Gdiplus::Graphics* pGraphics)
{
	if (_character->Visible == false)
		return;

	Gdiplus::Font F(L"Arial", 5, FontStyleBold, UnitMillimeter);

	PointF P(_character->x, _character->y - _character->AniUnits[_character->curState][0].Height);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = std::to_wstring(_character->hp) + L"/" + std::to_wstring(_character->maxHp);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printTitle(Gdiplus::Graphics* pGraphics)
{
	// 바탕 그림 깔기
	StaticObject* titleBg = new StaticObject();
	titleBg->Objtype = eObjectType_None;
	titleBg->AssetFileName = TEXT("title_stage_bg.png");
	titleBg->ImgRC = Rect(0, 0, 350, 86);
	titleBg->ViewRC = titleBg->ImgRC;
	titleBg->ViewRC.X = 550;
	titleBg->ViewRC.Y = 10;

	auto pImg = (AssetManager::GetInstance().GetImage(titleBg->AssetFileName)).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
	{
		//gray scale conversion:
		Gdiplus::ColorMatrix matrix =
		{
			.3f, .3f, .3f,   0,   0,
			.6f, .6f, .6f,   0,   0,
			.1f, .1f, .1f,   0,   0,
			0,   0,   0,   1,   0,
			0,   0,   0,   0,   1
		};

		Gdiplus::ImageAttributes attr;
		attr.SetColorMatrix(&matrix,
			Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		pGraphics->DrawImage(pImg.get(), titleBg->ViewRC, titleBg->ImgRC.X, titleBg->ImgRC.Y, titleBg->ImgRC.Width, titleBg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			&attr, 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), titleBg->ViewRC, titleBg->ImgRC.X, titleBg->ImgRC.Y, titleBg->ImgRC.Width, titleBg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 글자 출력
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	PointF P(titleBg->ViewRC.X + 35, titleBg->ViewRC.Y + 15);

	SolidBrush B(Color(255, 255, 255));

	wstring tempStr = L"프롤로그 마녀의 훈련장 \n";
	// TODO. 나중에 진짜 수치로 바꿔주기
	tempStr = tempStr + L"    wave " + std::to_wstring(GameManager::GetInstance().curWaveNum + 1);
	tempStr = tempStr + L"\t" + std::to_wstring(GameManager::GetInstance().remainEnemyNum) + L"/" + std::to_wstring(GameManager::GetInstance().curEnemyList.size());

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}