#include "pch.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("testbg.png");
	bg->rc = Rect(0, 0, 468, 900);

	infoStaticObj.emplace_back(bg);
}