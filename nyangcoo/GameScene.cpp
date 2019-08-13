#include "pch.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

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

	// 플레이어 생성
	Player* samplePlayer = new Player();
	samplePlayer->PlayerXmlFileName = "Asset\\player\\player_pistachio.xml";
	XmlManager::GetInstance().ParsePlayerData(*samplePlayer);
	samplePlayer->Init(new InputComponent(), new PlayerGraphicsComponent());

	infoObj.emplace_back(samplePlayer);

	Player* samplePlayer2 = new Player();
	samplePlayer2->PlayerXmlFileName = "Asset\\player\\player_whitechoco.xml";
	XmlManager::GetInstance().ParsePlayerData(*samplePlayer2);
	samplePlayer2->Init(new InputComponent(), new PlayerGraphicsComponent());

	samplePlayer2->x += 150; // samplePlayer보다 앞서 가게 하기 위해

	infoObj.emplace_back(samplePlayer2);

	// 적 생성
	Enemy* sampleEnemy = new Enemy();
	sampleEnemy->EnemyXmlFileName = "Asset\\player\\player_muscle.xml";
	XmlManager::GetInstance().ParseEnemyData(*sampleEnemy);
	sampleEnemy->Init(new InputComponent(), new PlayerGraphicsComponent());

	infoObj.emplace_back(sampleEnemy);

	// 테스트용 이펙트
	Effect* ef = new Effect();
	ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
	XmlManager::GetInstance().ParseEffectData(*ef);
	ef->Init(new EffectGraphicsComponent());

	infoObj.emplace_back(ef);

	Btn* BackTitleBtn = new Btn();
	BackTitleBtn->ID = eScene_Start;
	BackTitleBtn->AssetFileName = TEXT("back_btn.png");
	BackTitleBtn->rc = Rect(0, 0, 200, 60);
	BackTitleBtn->x = 630;
	BackTitleBtn->y = 10;

	infoStaticObj.emplace_back(BackTitleBtn);
}

void GameScene::Init()
{
	int tempCnt = 0;
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		if (it->Objtype == eObjectType_Player) // 플레이어일 경우
		{
			Player* player = reinterpret_cast<Player*>(it);
			player->Init();

			//TODO. 이부분은 캐릭터들이 겹치지 않게하기위함이다. 유닛 생성 버튼이 완성되면 지워야 함.
			it->x = 250 + 150 * tempCnt;
			tempCnt++;
		}
		else if (it->Objtype == eObjectType_Enemy) // 적일 경우
		{
			Enemy* enemy = reinterpret_cast<Enemy*>(it);
			enemy->Init();
		}
		else if (it->Objtype == eObjectType_Effect) // 이펙트일 경우
		{
			it->Enable = true;
		}
		else
		{

		}
	}
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