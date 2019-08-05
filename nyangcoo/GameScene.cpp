#include "pch.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{
	Name = "Scene_Game";

	bg = new StaticObject();
	Image* bgImg = new Image(TEXT("Asset\\testbg.png"));
	bg->Img = bgImg;
	bg->rc = Rect(0, 0, 1080, 1920);
}