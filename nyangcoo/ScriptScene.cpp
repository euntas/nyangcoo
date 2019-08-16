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

	//ScriptChoice = new StaticObject();
	//ScriptChoice->Objtype = eObjectType_None;
	//ScriptChoice->AssetFileName = TEXT("script_scene_choice.png");
	//ScriptChoice->ImgRC = Rect(0, 0, 1000, 248);
	//ScriptChoice->ViewRC = ScriptChoice->ImgRC;
	//ScriptChoice->x = 355;
	//ScriptChoice->y = 412;

	ScriptPlayer = new StaticObject();
	ScriptPlayer->Objtype = eObjectType_None;
	ScriptPlayer->AssetFileName = TEXT("script_scene_player.png");
	ScriptPlayer->ImgRC = Rect(0, 0, 301, 277);
	ScriptPlayer->ViewRC = ScriptPlayer->ImgRC;
	ScriptPlayer->x = 20;
	ScriptPlayer->y = 389;

	Btn* ChoiceBtn1 = new Btn();
	ChoiceBtn1->ID = eScene_Game;
	ChoiceBtn1->AssetFileName = TEXT("ChoiceBtn.png");
	ChoiceBtn1->ImgRC = Rect(0, 0, 935, 50);
	ChoiceBtn1->ViewRC = ChoiceBtn1->ImgRC;
	ChoiceBtn1->x = 415;
	ChoiceBtn1->y = 522;

	Btn* ChoiceBtn2 = new Btn();
	ChoiceBtn2->ID = eScene_Exit;
	ChoiceBtn2->AssetFileName = TEXT("ChoiceBtn.png");
	ChoiceBtn2->ImgRC = Rect(0, 0, 935, 50);
	ChoiceBtn2->ViewRC = ChoiceBtn2->ImgRC;
	ChoiceBtn2->x = 415;
	ChoiceBtn2->y = 602;

	infoStaticObj.emplace_back(bg);
	infoStaticObj.emplace_back(ChapterName);
	infoStaticObj.emplace_back(ScriptText);
	infoStaticObj.emplace_back(ScriptChoice);
	infoStaticObj.emplace_back(ScriptPlayer);
	infoStaticObj.emplace_back(ChoiceBtn1);
	infoStaticObj.emplace_back(ChoiceBtn2);
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
	printChoice(pGraphics);
}

void ScriptScene::Release()
{

}

void ScriptScene::printChoice(Gdiplus::Graphics* pGraphics)
{
	// 바탕 그림 깔기
	StaticObject* ScriptChoice = new StaticObject();
	ScriptChoice->Objtype = eObjectType_None;
	ScriptChoice->AssetFileName = TEXT("script_scene_choice.png");
	ScriptChoice->ImgRC = Rect(0, 0, 1000, 248);
	ScriptChoice->ViewRC = ScriptChoice->ImgRC;
	ScriptChoice->ViewRC.X = 355;
	ScriptChoice->ViewRC.Y = 412;
	//ScriptChoice->ViewRC = ScriptChoice->ImgRC;
	//ScriptChoice->x = 355;
	//ScriptChoice->y = 412;

	auto pImg = (AssetManager::GetInstance().GetImage(ScriptChoice->AssetFileName)).lock();

	pGraphics->DrawImage(pImg.get(), ScriptChoice->ViewRC, ScriptChoice->ImgRC.X, ScriptChoice->ImgRC.Y, ScriptChoice->ImgRC.Width, ScriptChoice->ImgRC.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// 글자 출력 390 418
	Gdiplus::Font F(L"Arial", 5, FontStyleBold, UnitMillimeter);

	Gdiplus::PointF P1(ScriptChoice->ViewRC.X + 45, ScriptChoice->ViewRC.Y + 25);

	Gdiplus::SolidBrush B1(Color(13, 48, 119));

	wstring tempTex = L"휴..간신히 막아냈지만 저 고양이들이 마법사들의 도시로 가면 모두가 위험해질거야..\n이제 어떻게 해야 좋을까?";

	// TODO. 나중에 진짜 수치로 바꿔주기
	pGraphics->DrawString(tempTex.c_str(), -1, &F, P1, &B1);

	Gdiplus::PointF P2(ScriptChoice->ViewRC.X + 115, ScriptChoice->ViewRC.Y + 110);
	Gdiplus::SolidBrush B2(Color(76, 40, 113));

	wstring tempCho = L"마법사들의 도시에 알린다.\n\n\n\n마법사들의 도시로 향하는 [냥국] 병사들을 공격한다.";

	pGraphics->DrawString(tempCho.c_str(), -1, &F, P2, &B2);
}