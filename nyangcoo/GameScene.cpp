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

	// 배경 그림 깔기
	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg_bamboo2.png");
	bg->ImgRC = Rect(0, 0, 2840, 672);
	bg->ViewRC = Rect(0, 0, 1420, 672);

	infoStaticObj.emplace_back(bg);

	// 캐릭터 생성용 슬롯 버튼 만들기
	std::string charNameList[8] = { "pistachio",  "whitechoco", "muscle", "kiwi", "windarcher", "pistachio", "whitechoco", "kiwi" };
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
	CommandPlayer = new Character(eObjectType_Player);
	CommandPlayer->CharacterXmlFileName = "Asset\\player\\player_moonlight.xml";
	XmlManager::GetInstance().ParseCharacterData(*CommandPlayer);
	CommandPlayer->Init(new InputComponent(), new CharacterGraphicsComponent(CommandPlayer));

	infoObj.emplace_back(CommandPlayer);

	// 적 생성
	Character* sampleEnemy = new Character(eObjectType_Enemy);
	sampleEnemy->CharacterXmlFileName = "Asset\\player\\player_muscle.xml";
	XmlManager::GetInstance().ParseCharacterData(*sampleEnemy);
	sampleEnemy->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy));

	Character* sampleEnemy2 = new Character(eObjectType_Enemy);
	sampleEnemy2->CharacterXmlFileName = "Asset\\player\\player_titan.xml";
	XmlManager::GetInstance().ParseCharacterData(*sampleEnemy2);
	sampleEnemy2->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy2));
	sampleEnemy2->bleft = true;

	Character* sampleEnemy3 = new Character(eObjectType_Enemy);
	sampleEnemy3->CharacterXmlFileName = "Asset\\player\\player_titan.xml";
	XmlManager::GetInstance().ParseCharacterData(*sampleEnemy3);
	sampleEnemy3->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy3));
	sampleEnemy3->x = sampleEnemy2->x + 600;
	sampleEnemy3->bleft = true;

	infoObj.emplace_back(sampleEnemy);
	infoObj.emplace_back(sampleEnemy2);
	infoObj.emplace_back(sampleEnemy3);

	// 테스트용 이펙트
	Effect* ef = new Effect();
	ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
	XmlManager::GetInstance().ParseEffectData(*ef);
	ef->x = 700; 
	ef->y = 420;
	ef->Init(new EffectGraphicsComponent(ef));

	infoObj.emplace_back(ef);

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

}

void GameScene::InitGoldBar()
{
	goldBg = new StaticObject();
	goldBg->AssetFileName = TEXT("goldbar\\goldbar_bg.png");
	goldBg->ImgRC = Rect(0, 0, 417, 113);
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
			goldPart[i]->y = goldBg->y + 25;
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
	Scene::Update(Delta);

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
	ic->ImgRC = Rect(0, 0, 19, 22);
	ic->ViewRC = Rect(0, 0, 40, 37);
	ic->ViewRC.X = goldBg->x + 100;
	ic->ViewRC.Y = goldBg->y + 40;

	auto pImg = (AssetManager::GetInstance().GetImage(ic->AssetFileName)).lock();

	pGraphics->DrawImage(pImg.get(), ic->ViewRC, ic->ImgRC.X, ic->ImgRC.Y, ic->ImgRC.Width, ic->ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// 글자 출력
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(goldBg->x + 130.0f, goldBg->y + 35.0f);

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

	pGraphics->DrawImage(pImg.get(), titleBg->ViewRC, titleBg->ImgRC.X, titleBg->ImgRC.Y, titleBg->ImgRC.Width, titleBg->ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// 글자 출력
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	PointF P(titleBg->ViewRC.X + 35, titleBg->ViewRC.Y + 15);

	SolidBrush B(Color(255, 255, 255));

	wstring tempStr = L"프롤로그 마녀의 훈련장 \n";
	// TODO. 나중에 진짜 수치로 바꿔주기
	tempStr = tempStr + L"    wave " + std::to_wstring(1);
	tempStr = tempStr + L"\t" + std::to_wstring(10) + L"/" + std::to_wstring(10);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}