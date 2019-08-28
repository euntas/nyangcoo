#include "pch.h"
#include "StartScene.h"

StartScene::StartScene() : Scene()
{
	name = "Scene_Start";

	Init();
}

void StartScene::Init()
{
	infoStaticObj.clear();

	bg = new StaticObject();
	bg->setObjtype(eObjectType_BGImage);
	bg->setAssetFileName(TEXT("bg.png"));
	bg->setImgRC(Rect(0, 0, 1420, 672));
	bg->setViewRC(bg->getImgRC());
	infoStaticObj.emplace_back(bg);

	Btn* StartBtn = new Btn(eScene_ChapterSelect, TEXT("title_btn_00.png"), Rect(0, 0, 236, 72), Rect(0, 0, 236, 72), 600, 200, 0);
	StartBtn->setIsClicked(false);
	infoStaticObj.emplace_back(StartBtn);

	Btn* ContinueBtn = new Btn(eScene_Continue, TEXT("title_btn_01.png"), Rect(0, 0, 236, 72), Rect(0, 0, 236, 72), 600, 290, 0);
	infoStaticObj.emplace_back(ContinueBtn);

	Btn* LoadGameBtn = new Btn(eScene_LoadGame, TEXT("title_btn_02.png"), Rect(0, 0, 236, 72), Rect(0, 0, 236, 72), 600, 380, 0);
	infoStaticObj.emplace_back(LoadGameBtn);

	Btn* ChallengeBtn = new Btn(eScene_SaveGame, TEXT("title_btn_03.png"), Rect(0, 0, 236, 72), Rect(0, 0, 236, 72), 600, 470, 0);
	infoStaticObj.emplace_back(ChallengeBtn);

	Btn* ExitBtn = new Btn(eScene_Exit, TEXT("title_btn_04.png"), Rect(0, 0, 236, 72), Rect(0, 0, 236, 72), 600, 560, 0);
	infoStaticObj.emplace_back(ExitBtn);

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());
	popUp->setVisible(false);
	infoStaticObj.emplace_back(popUp);
}

void StartScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void StartScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
}

void StartScene::Release()
{

}

