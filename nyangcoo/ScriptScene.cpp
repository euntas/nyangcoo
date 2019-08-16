#include "pch.h"
#include "ScriptScene.h"

ScriptScene::ScriptScene() : Scene()
{
	Name = "Scene_Script";

	bg = new StaticObject();
	bg->Objtype = eObjectType_BGImage;
	bg->AssetFileName = TEXT("script_scene_bg.png");
	bg->ImgRC = Rect(0, 0, 1420, 672);
	bg->ViewRC = bg->ImgRC;

	ChapterName = new StaticObject();
	ChapterName->Objtype = eObjectType_None;
	ChapterName->AssetFileName = TEXT("chapter_title.png");
	ChapterName->ImgRC = Rect(0, 0, 553, 111);
	ChapterName->ViewRC = ChapterName->ImgRC;
	ChapterName->x = 470;
	ChapterName->y = 8;

	ScriptText = new StaticObject();
	ScriptText->Objtype = eObjectType_None;
	ScriptText->AssetFileName = TEXT("script_scene_text.png");
	ScriptText->ImgRC = Rect(0, 0, 1300, 250);
	ScriptText->ViewRC = ScriptText->ImgRC;
	ScriptText->x = 58;
	ScriptText->y = 123;

	ScriptChoice = new StaticObject();
	ScriptChoice->Objtype = eObjectType_None;
	ScriptChoice->AssetFileName = TEXT("script_scene_choice.png");
	ScriptChoice->ImgRC = Rect(0, 0, 1000, 248);
	ScriptChoice->ViewRC = ScriptChoice->ImgRC;
	ScriptChoice->x = 355;
	ScriptChoice->y = 412;

	ScriptPlayer = new StaticObject();
	ScriptPlayer->Objtype = eObjectType_None;
	ScriptPlayer->AssetFileName = TEXT("script_scene_player.png");
	ScriptPlayer->ImgRC = Rect(0, 0, 301, 277);
	ScriptPlayer->ViewRC = ScriptPlayer->ImgRC;
	ScriptPlayer->x = 20;
	ScriptPlayer->y = 389;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(ChapterName);
	infoStaticObj.emplace_back(ScriptText);
	infoStaticObj.emplace_back(ScriptChoice);
	infoStaticObj.emplace_back(ScriptPlayer);
}

void ScriptScene::Init()
{

}

void ScriptScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void ScriptScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void ScriptScene::Release()
{

}