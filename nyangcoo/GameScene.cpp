#include "pch.h"
#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	Init();
}

void GameScene::Init()
{
	// �ʱ� ��ġ �ο�
	ClearAll();

	gsGoldDeltaA = 0;
	gold = 1000;
	gsGoldDelta = 500; // ��� ���� �ʱ� �ӵ�

	// ��� �׸� ���
	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg_bamboo2.png");
	bg->ImgRC = Rect(0, 0, 2840, 672);
	bg->ViewRC = Rect(0, 0, 1420, 672);

	infoStaticObj.emplace_back(bg);

	// ĳ���� ������ ���� ��ư �����
	MakeCharacterBtn* mcb = new MakeCharacterBtn("pistachio");
	infoStaticObj.emplace_back(mcb);

	UpgradeCharacterBtn* ucb = new UpgradeCharacterBtn(mcb);
	infoStaticObj.emplace_back(ucb);

	MakeCharacterBtn* mcb2 = new MakeCharacterBtn("whitechoco");
	mcb2->x = mcb->x + 100;
	infoStaticObj.emplace_back(mcb2);

	UpgradeCharacterBtn* ucb2 = new UpgradeCharacterBtn(mcb2);
	ucb2->x = ucb->x + 100;
	infoStaticObj.emplace_back(ucb2);

	MakeCharacterBtn* mcb3 = new MakeCharacterBtn("muscle");
	mcb3->x = mcb2->x + 100;
	infoStaticObj.emplace_back(mcb3);

	UpgradeCharacterBtn* ucb3 = new UpgradeCharacterBtn(mcb3);
	ucb3->x = ucb2->x + 100;
	infoStaticObj.emplace_back(ucb3);

	MakeCharacterBtn* mcb4 = new MakeCharacterBtn("kiwi");
	mcb4->x = mcb3->x + 100;
	infoStaticObj.emplace_back(mcb4);

	UpgradeCharacterBtn* ucb4 = new UpgradeCharacterBtn(mcb4);
	ucb4->x = ucb3->x + 100;
	infoStaticObj.emplace_back(ucb4);

	MakeCharacterBtn* mcb5 = new MakeCharacterBtn("windarcher");
	mcb5->x = mcb4->x + 100;
	infoStaticObj.emplace_back(mcb5);

	UpgradeCharacterBtn* ucb5 = new UpgradeCharacterBtn(mcb5);
	ucb5->x = ucb4->x + 100;
	infoStaticObj.emplace_back(ucb5);

	MakeCharacterBtn* mcb6 = new MakeCharacterBtn("windarcher");
	mcb6->x = mcb5->x + 100;
	infoStaticObj.emplace_back(mcb6);

	UpgradeCharacterBtn* ucb6 = new UpgradeCharacterBtn(mcb6);
	ucb6->x = ucb5->x + 100;
	infoStaticObj.emplace_back(ucb6);

	MakeCharacterBtn* mcb7 = new MakeCharacterBtn("windarcher");
	mcb7->x = mcb6->x + 100;
	infoStaticObj.emplace_back(mcb7);

	UpgradeCharacterBtn* ucb7 = new UpgradeCharacterBtn(mcb7);
	ucb7->x = ucb6->x + 100;
	infoStaticObj.emplace_back(ucb7);

	// �÷��̾� ����
	Character* CommandPlayer = new Character(eObjectType_Player);
	CommandPlayer->CharacterXmlFileName = "Asset\\player\\player_moonlight.xml";
	XmlManager::GetInstance().ParseCharacterData(*CommandPlayer);
	CommandPlayer->Init(new InputComponent(), new CharacterGraphicsComponent(CommandPlayer));

	infoObj.emplace_back(CommandPlayer);

	// �� ����
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

	// �׽�Ʈ�� ����Ʈ
	Effect* ef = new Effect();
	ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
	XmlManager::GetInstance().ParseEffectData(*ef);
	ef->Init(new EffectGraphicsComponent(ef));

	infoObj.emplace_back(ef);

	// TODO. ���߿� �����ʿ�. �˾� �κ�
	PopUp* popUp = new PopUp(ePopup_close);

	//PopUp = new StaticObject();
	//popUp->Objtype = eObjectType_PopUp;
	//popUp->AssetFileName = TEXT("popup_all.png");
	popUp->Visible = false;
	popUp->ImgRC = Rect(0, 0, 250, 198);
	popUp->ViewRC = popUp->ImgRC;

	infoStaticObj.emplace_back(popUp);

	// TODO. ���߿� �����
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

	// ��� ��
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
			goldPart[i]->x = goldPart[i-1]->x + 36;
			goldPart[i]->y = goldPart[i-1]->y;
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

		// max���� ������ ��� ������Ŵ
		
		if (gold < maxGold)
		{
			gold += 10;
		}	
	}

	// ���� ������� ���
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
}

void GameScene::Release()
{
	Scene::Release();
}

void GameScene::printGold(int _gold, Graphics* pGraphics)
{
	Gdiplus::Font F(L"Arial", 10, FontStyleBold, UnitMillimeter);

	PointF P(10.0f, 100.0f);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = L"��� : " + std::to_wstring(_gold) + L"/" + std::to_wstring(maxGold);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printTitle(Gdiplus::Graphics* pGraphics)
{
	// ���� �׸� ���
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

	// ���� ���
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	PointF P(titleBg->ViewRC.X + 35, titleBg->ViewRC.Y + 15);

	SolidBrush B(Color(255, 255, 255));

	wstring tempStr = L"���ѷα� ������ �Ʒ��� \n";
	// TODO. ���߿� ��¥ ��ġ�� �ٲ��ֱ�
	tempStr = tempStr + L"    wave " + std::to_wstring(1);
	tempStr = tempStr + L"\t" + std::to_wstring(10) + L"/" + std::to_wstring(10);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}