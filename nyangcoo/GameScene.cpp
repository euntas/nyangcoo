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
	bg->AssetFileName = TEXT("bg_bamboo.png");
	bg->rc = Rect(0, 0, 1420, 672);

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

	infoObj.emplace_back(sampleEnemy);

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
	popUp->rc = Rect(0, 0, 250, 198);
	popUp->Visible = false;

	infoStaticObj.emplace_back(popUp);

	// TODO. ���߿� �����
	Btn* ExitBtn = new Btn();
	ExitBtn->ID = eScene_Exit;
	ExitBtn->AssetFileName = TEXT("title_btn_04.png");
	ExitBtn->rc = Rect(0, 0, 236, 72);
	ExitBtn->x = 1200;
	ExitBtn->y = 5;

	infoStaticObj.emplace_back(ExitBtn);
}

void GameScene::Update(float Delta)
{
	Scene::Update(Delta);

	gsGoldDeltaA += Delta;

	if (gsGoldDeltaA > gsGoldDelta)
	{
		gsGoldDeltaA = 0;

		gold += 10;
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

	PointF P(10.0f, 10.0f);

	SolidBrush B(Color(0, 0, 0));

	wstring tempStr = L"��� : " + std::to_wstring(_gold);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void GameScene::printTitle(Gdiplus::Graphics* pGraphics)
{
	// ���� �׸� ���
	StaticObject* titleBg = new StaticObject();
	titleBg->Objtype = eObjectType_None;
	titleBg->AssetFileName = TEXT("title_stage_bg.png");
	titleBg->rc = Rect(0, 0, 350, 86);
	titleBg->x = 550;
	titleBg->y = 10;

	auto pImg = (AssetManager::GetInstance().GetImage(titleBg->AssetFileName)).lock();

	Rect tempRC(titleBg->x, titleBg->y, titleBg->rc.Width, titleBg->rc.Height);
	pGraphics->DrawImage(pImg.get(), tempRC, titleBg->rc.X, titleBg->rc.Y, titleBg->rc.Width, titleBg->rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// ���� ���
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	PointF P(titleBg->x + 35, titleBg->y + 15);

	SolidBrush B(Color(255, 255, 255));

	wstring tempStr = L"���ѷα� ������ �Ʒ��� \n";
	// TODO. ���߿� ��¥ ��ġ�� �ٲ��ֱ�
	tempStr = tempStr + L"    wave " + std::to_wstring(1);
	tempStr = tempStr + L"\t" + std::to_wstring(10) + L"/" + std::to_wstring(10);

	pGraphics->DrawString(tempStr.c_str(), -1, &F, P, &B);
}