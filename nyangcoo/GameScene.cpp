#include "pch.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	bg = new StaticObject();
	bg->AssetFileName = TEXT("testbg.png");
	bg->rc = Rect(0, 0, 1080, 1920);
}