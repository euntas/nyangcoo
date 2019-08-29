#include "pch.h"
#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	name = "Scene_Game";

	Init();
}

void GameScene::Init()
{
	// 초기 수치 부여
	ClearAll();

	gsGoldDeltaA = 0;
	gold = 1000;
	gsGoldDelta = 550; // 골드 증가 초기 속도

	// 게임 매니저 초기화
	int selectedStageId = GameManager::GetInstance().btnID;
	GameManager::GetInstance().Init(selectedStageId);

	maxGold = GameManager::GetInstance().curStage->getMaxGold();

	// 배경 그림 깔기
	bg = GameManager::GetInstance().curStage->bg;
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_Background, bg));

	// 캐릭터 생성용 슬롯 버튼 만들기
	std::string charNameList[8];

	for (int i = 0; i < MAX_SELECT_COOKIE_NUM; i++)
	{
		charNameList[i] = GameManager::GetInstance().characterSelectedList[i];
	}

	charNameList[5] = "lemon";
	charNameList[6] = "plum";
	charNameList[7] = "moonrabit";

	MakeCharacterBtn* mcb[8];
	UpgradeCharacterBtn* ucb[8];

	for (int n = 0; n < 8; n++)
	{
		mcb[n] = new MakeCharacterBtn(charNameList[n]);
		if (n > 0)
			mcb[n]->setX(mcb[n-1]->getX() + 100);
		infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, mcb[n]));

		ucb[n] = new UpgradeCharacterBtn(mcb[n]);
		if (n > 0)
			ucb[n]->setX(ucb[n - 1]->getX() + 100);
		infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, ucb[n]));
	}
	
	// 플레이어 생성
	CommandPlayer = GameManager::GetInstance().CommandPlayer;
	infoObj.insert(pair<int, Object*>(eLayer_Character, GameManager::GetInstance().CommandPlayer));

	// 적 생성
	for (auto& it : GameManager::GetInstance().curEnemyList)
	{
		infoObj.insert(pair<int, Object*>(eLayer_Character, it));
	}

	Btn* HelpBtn = new Btn(eScene_Help, TEXT("help_btn.png"), Rect(0, 0, 65, 65), Rect(0, 0, 65, 65), 1350, 20, selectedStageId);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, HelpBtn));

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->setVisible(false);
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());

	infoUIObj.insert(pair<int, StaticObject*>(eLayer_Popup, popUp));

	// 골드 바
	InitGoldBar();

	// 플레이어 스킬
	PlayerSkillBtn* ps_heal = new PlayerSkillBtn("heal");
	ps_heal->btnImg->setX(910);
	ps_heal->btnImg->setY(525);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, ps_heal));

	PlayerSkillBtn* ps_blizzard = new PlayerSkillBtn("blizzard");
	ps_blizzard->btnImg->setX(ps_heal->btnImg->getX() + 150);
	ps_blizzard->btnImg->setY(ps_heal->btnImg->getY());
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, ps_blizzard));

	PlayerSkillBtn* ps_razer = new PlayerSkillBtn("razer");
	ps_razer->btnImg->setX(ps_blizzard->btnImg->getX() + 150);
	ps_razer->btnImg->setY(ps_heal->btnImg->getY());
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, ps_razer));

	// 플레이어 업그레이드 버튼 (골드 획득속도 증가)
	Btn* UpgradeBtn = new Btn(ePlayerUpgradeBtn, TEXT("slot\\up_slot_100.png"), Rect(0, 0, 200, 100), Rect(0, 0, 200, 100), GameManager::GetInstance().CommandPlayer->getX() - 75, GameManager::GetInstance().CommandPlayer->getY() - GameManager::GetInstance().CommandPlayer->AniUnits[0][0].Height - 100, selectedStageId);
	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, UpgradeBtn));

	ResultPopUp = new PopUp(ePopup_result);
	infoUIObj.insert(pair<int, StaticObject*>(eLayer_Popup, ResultPopUp));

	// 물음표 눌렀을때 나타나는 그림
	StaticObject* questionImg = new StaticObject();
	questionImg->setAssetFileName(L"help_popup.png");
	questionImg->setImgRC(Rect(0, 0, 1300, 600));
	questionImg->setViewRC(questionImg->getImgRC());
	questionImg->setX(60);
	questionImg->setY(50);
	questionImg->setVisible(false);

	infoUIObj.insert(pair<int, StaticObject*>(eLayer_UI, questionImg));


	GameManager::GetInstance().IsGrayScale = false;
}

void GameScene::InitGoldBar()
{
	goldBg = new StaticObject();
	goldBg->setAssetFileName(TEXT("goldbar\\goldbar_bg.png"));
	goldBg->setImgRC(Rect(0, 0, 414, 102));
	goldBg->setViewRC(goldBg->getImgRC());
	goldBg->setX(10);
	goldBg->setY(10);

	infoStaticObj.insert(pair<int, StaticObject*>(eLayer_Background, goldBg));

	for (int i = 0; i < 10; i++)
	{
		goldPart[i] = new StaticObject();
		goldPart[i]->setAssetFileName(TEXT("goldbar\\goldbar_unit_brown.png"));
		goldPart[i]->setImgRC(Rect(0, 0, 36, 64));
		goldPart[i]->setViewRC(goldPart[i]->getImgRC());
		if (i == 0)
		{
			goldPart[i]->setX(goldBg->getX() + 25);
			goldPart[i]->setY(goldBg->getY() + 19);
		}
		else
		{
			goldPart[i]->setX(goldPart[i - 1]->getX() + 36);
			goldPart[i]->setY(goldPart[i - 1]->getY());
		}

		infoStaticObj.insert(pair<int, StaticObject*>(eLayer_UI, goldPart[i]));
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
			ResultPopUp->bg->setAssetFileName(TEXT("result_lose.png"));
		}
		else
		{
			GameManager::GetInstance().coin += 700;
			GameManager::GetInstance().stageClearList[GameManager::GetInstance().curStage->getStageID() + 1] = true;
		}
		ResultPopUp->setVisible(true);
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
			goldPart[i]->setAssetFileName(TEXT("goldbar\\goldbar_unit_yellow.png"));
		else
			goldPart[i]->setAssetFileName(TEXT("goldbar\\goldbar_unit_brown.png"));
	}

	// wave관련 코드
	if (GameManager::GetInstance().IsAllEnemyDead())
	{
		if (GameManager::GetInstance().ChangeWave())
		{
			for (auto& it : GameManager::GetInstance().curEnemyList)
			{
				infoObj.insert(pair<int, Object*>(eLayer_Character, it));
			}
		}
	}

}

void GameScene::Render(Graphics* pGraphics)
{
	
	Scene::Render(pGraphics);

	printTitle(pGraphics);

	if (ResultPopUp->getVisible() == true)
	{
		if (GameManager::GetInstance().IsWin)
			printCoin(700, pGraphics);
		else
			printCoin(0, pGraphics);
	}

	for (auto& it : infoUIObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if (obj->getObjtype() == eObjectType_None && obj->getAssetFileName() == L"help_popup.png")
		{
			if (obj->getVisible() == false)
			{
				printGold(gold, pGraphics);
				printHP(CommandPlayer, pGraphics);
			}
		}
	}
	
}

void GameScene::Release()
{
	Scene::Release();
}

void GameScene::printGold(int _gold, Graphics* pGraphics)
{
	// 아이콘이미지 출력
	StaticObject* ic = new StaticObject();
	ic->setObjtype(eObjectType_None);
	ic->setAssetFileName(TEXT("goldbar\\gold_icon.png"));
	ic->setImgRC(Rect(0, 0, 40, 39));
	ic->setViewRC(Rect(goldBg->getX() + 100, goldBg->getY() + 34, 40, 39));

	auto pImg = (AssetManager::GetInstance().GetImage(ic->getAssetFileName())).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		pGraphics->DrawImage(pImg.get(), ic->getViewRC(), ic->getImgRC().X, ic->getImgRC().Y, ic->getImgRC().Width, ic->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), ic->getViewRC(), ic->getImgRC().X, ic->getImgRC().Y, ic->getImgRC().Width, ic->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 글자 출력
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(goldBg->getX() + 130.0f, goldBg->getY() + 29.0f);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = std::to_wstring(_gold) + L"/" + std::to_wstring(maxGold);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printHP(Character* _character, Gdiplus::Graphics* pGraphics)
{
	if (_character->getVisible() == false)
		return;

	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(_character->getX(), _character->getY() - _character->AniUnits[_character->curState][0].Height);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = std::to_wstring(_character->hp) + L"/" + std::to_wstring(_character->maxHp);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printCoin(int coin, Gdiplus::Graphics* pGraphics)
{
	// 글자 출력
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(ResultPopUp->getX() + 280.0f, ResultPopUp->getY() + 230.0f);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = std::to_wstring(coin);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printTitle(Gdiplus::Graphics* pGraphics)
{
	// 바탕 그림 깔기
	StaticObject* titleBg = new StaticObject();
	titleBg->setObjtype(eObjectType_None);
	titleBg->setAssetFileName(TEXT("title_stage_bg.png"));
	titleBg->setImgRC(Rect(0, 0, 350, 86));
	titleBg->setViewRC(Rect(550, 10, 350, 86));

	auto pImg = (AssetManager::GetInstance().GetImage(titleBg->getAssetFileName())).lock();

	if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Game")
	{
		pGraphics->DrawImage(pImg.get(), titleBg->getViewRC(), titleBg->getImgRC().X, titleBg->getImgRC().Y, titleBg->getImgRC().Width, titleBg->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			AssetManager::GetInstance().getGrayScaleAttr(), 0, nullptr);
	}
	else
	{
		pGraphics->DrawImage(pImg.get(), titleBg->getViewRC(), titleBg->getImgRC().X, titleBg->getImgRC().Y, titleBg->getImgRC().Width, titleBg->getImgRC().Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	// 글자 출력
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	PointF P(titleBg->getViewRC().X + 35, titleBg->getViewRC().Y + 15);

	SolidBrush B(Color(255, 255, 255));

	wstring tempStr = GameManager::GetInstance().curStage->getStageTitle();
	// TODO. 나중에 진짜 수치로 바꿔주기
	tempStr = tempStr + L"    wave " + std::to_wstring(GameManager::GetInstance().curWaveNum + 1);
	tempStr = tempStr + L"\t" + std::to_wstring(GameManager::GetInstance().remainEnemyNum) + L"/" + std::to_wstring(GameManager::GetInstance().curEnemyList.size());

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}