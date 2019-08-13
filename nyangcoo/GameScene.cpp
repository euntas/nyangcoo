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

	// �÷��̾� ����
	Player* samplePlayer = new Player();
	samplePlayer->PlayerXmlFileName = "Asset\\player\\player_brave.xml";
	XmlManager::GetInstance().ParsePlayerData(*samplePlayer);
	samplePlayer->Init(new InputComponent(), new PlayerGraphicsComponent());

	infoObj.emplace_back(samplePlayer);

	Player* samplePlayer2 = new Player();
	samplePlayer2->PlayerXmlFileName = "Asset\\player\\player_muscle.xml";
	XmlManager::GetInstance().ParsePlayerData(*samplePlayer2);
	samplePlayer2->Init(new InputComponent(), new PlayerGraphicsComponent());

	samplePlayer2->x += 150; // samplePlayer���� �ռ� ���� �ϱ� ����

	infoObj.emplace_back(samplePlayer2);

	// �׽�Ʈ�� ����Ʈ
	Effect* ef = new Effect();
	ef->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
	XmlManager::GetInstance().ParseEffectData(*ef);
	ef->Init(new EffectGraphicsComponent());

	infoObj.emplace_back(ef);



	PopUp* popUp = new PopUp();

	//PopUp = new StaticObject();
	//popUp->Objtype = eObjectType_PopUp;
	//popUp->AssetFileName = TEXT("sm_good.png");
	popUp->rc = Rect(0, 0, 250, 198);

	infoStaticObj.emplace_back(popUp);

}

void GameScene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// �÷��̾��� ���
		if (it->Objtype == eObjectType_Player)
		{
			
		}
		else if (it->Objtype == eObjectType_Effect) // ����Ʈ�� ���
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

}