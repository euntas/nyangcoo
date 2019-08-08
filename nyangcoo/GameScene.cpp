#include "pch.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("testbg.png");
	bg->rc = Rect(0, 0, 900, 468);

	infoStaticObj.emplace_back(bg);

	// 플레이어 생성
	Player* samplePlayer = new Player();
	samplePlayer->PlayerAssetFileName[eState_Run] = TEXT("player\\player_brave_walk.png");
	samplePlayer->PlayerAssetFileName[eState_Dead] = TEXT("player\\player_brave_end.png");
	samplePlayer->Init(new InputComponent(), new PlayerGraphicsComponent());

	infoObj.emplace_back(samplePlayer);
}

void GameScene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->Objtype == eObjectType_Player)
		{
			
		}
	}
}

void GameScene::Update(float Delta)
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->Objtype == eObjectType_Player)
		{
			it->Update(Delta);
		}
	}
}

void GameScene::Render(Graphics* pGraphics)
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->Objtype == eObjectType_Player)
		{
			it->Render(pGraphics);
		}
	}
}

void GameScene::Release()
{

}