#include "pch.h"
#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	Init();
}

void GameScene::Init()
{
	ClearAll();

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("bg_bamboo.png");
	bg->rc = Rect(0, 0, 1420, 672);

	infoStaticObj.emplace_back(bg);

	// TODO. 테스트용 나중에 진짜 본진 플레이어로 바꾸기
	StaticObject* CommandPlayer = new StaticObject();
	CommandPlayer->Objtype = eObjectType_None;
	CommandPlayer->AssetFileName = TEXT("player_monnlight_cookie_stand.jpg.png");
	CommandPlayer->rc = Rect(0, 0, 343, 237);
	CommandPlayer->x = 0;
	CommandPlayer->y = 250;

	infoStaticObj.emplace_back(CommandPlayer);

	// 캐릭터 생성용 슬롯 버튼 만들기
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

	// 플레이어 생성
	//Character* samplePlayer = new Character(eObjectType_Character);
	//samplePlayer->CharacterXmlFileName = "Asset\\player\\player_pistachio.xml";
	//XmlManager::GetInstance().ParseCharacterData(*samplePlayer);
	//samplePlayer->Init(new InputComponent(), new CharacterGraphicsComponent(samplePlayer));

	//infoObj.emplace_back(samplePlayer);

	//Character* samplePlayer2 = new Character(eObjectType_Character);
	//samplePlayer2->CharacterXmlFileName = "Asset\\player\\player_whitechoco.xml";
	//XmlManager::GetInstance().ParseCharacterData(*samplePlayer2);
	//samplePlayer2->Init(new InputComponent(), new CharacterGraphicsComponent(samplePlayer2));

	//samplePlayer2->x += 150; // samplePlayer보다 앞서 가게 하기 위해

	//infoObj.emplace_back(samplePlayer2);

	// 적 생성
	Character* sampleEnemy = new Character(eObjectType_Enemy);
	sampleEnemy->CharacterXmlFileName = "Asset\\player\\player_muscle.xml";
	XmlManager::GetInstance().ParseCharacterData(*sampleEnemy);
	sampleEnemy->Init(new InputComponent(), new CharacterGraphicsComponent(sampleEnemy));

	infoObj.emplace_back(sampleEnemy);

	// 테스트용 이펙트
	Effect* ef = new Effect();
	ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
	XmlManager::GetInstance().ParseEffectData(*ef);
	ef->Init(new EffectGraphicsComponent(ef));

	infoObj.emplace_back(ef);

	PopUp* popUp = new PopUp(ePopup_close);

	//PopUp = new StaticObject();
	//popUp->Objtype = eObjectType_PopUp;
	//popUp->AssetFileName = TEXT("popup_all.png");
	popUp->rc = Rect(0, 0, 250, 198);

	infoStaticObj.emplace_back(popUp);

}

void GameScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void GameScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void GameScene::Release()
{
	Scene::Release();
}