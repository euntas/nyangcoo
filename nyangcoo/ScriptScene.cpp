#include "pch.h"
#include "ScriptScene.h"

ScriptScene::ScriptScene() : Scene()
{
	name = "Scene_Script";

	Init();
}

void ScriptScene::Init()
{
	bg = new StaticObject();
	bg->setObjtype(eObjectType_BGImage);
	bg->setAssetFileName(TEXT("script_scene_bg.png"));
	bg->setImgRC(Rect(0, 0, 1420, 672));
	bg->setViewRC(bg->getImgRC());
	infoStaticObj.emplace_back(bg);

	ChapterName = new StaticObject();
	ChapterName->setObjtype(eObjectType_None);
	ChapterName->setAssetFileName(TEXT("chapter_title.png"));
	ChapterName->setImgRC(Rect(0, 0, 553, 111));
	ChapterName->setViewRC(ChapterName->getImgRC());
	ChapterName->setX(470);
	ChapterName->setY(8);
	infoStaticObj.emplace_back(ChapterName);

	ScriptPlayer = new StaticObject();
	ScriptPlayer->setObjtype(eObjectType_None);
	ScriptPlayer->setAssetFileName(TEXT("script_scene_player.png"));
	ScriptPlayer->setImgRC(Rect(0, 0, 301, 277));
	ScriptPlayer->setViewRC(ScriptPlayer->getImgRC());
	ScriptPlayer->setX(20);
	ScriptPlayer->setY(389);
	infoStaticObj.emplace_back(ScriptPlayer);

	Btn* ChoiceBtn1 = new Btn(eScene_ChapterSelect, TEXT("ChoiceBtn.png"), Rect(0, 0, 935, 50), Rect(0, 0, 935, 50), 415, 522, 0);
	ChoiceBtn1->setSelectOption(0);
	infoStaticObj.emplace_back(ChoiceBtn1);
	
	Btn* ChoiceBtn2 = new Btn(eScene_ChapterSelect, TEXT("ChoiceBtn.png"), Rect(0, 0, 935, 50), Rect(0, 0, 935, 50), 415, 602, 0);
	ChoiceBtn1->setSelectOption(1);
	infoStaticObj.emplace_back(ChoiceBtn2);

	PopUp* popUp = new PopUp(ePopup_close);
	popUp->setImgRC(Rect(0, 0, 271, 279));
	popUp->setViewRC(popUp->getImgRC());
	popUp->setVisible(false);
	infoStaticObj.emplace_back(popUp);
}

void ScriptScene::Update(float Delta)
{
	Scene::Update(Delta);
}

void ScriptScene::Render(Graphics* pGraphics)
{
	Scene::Render(pGraphics);
	printChoice(pGraphics);
	printGameResult(pGraphics);

	for (auto& it : infoStaticObj)
	{
		if (it == nullptr) continue;

		if (it->getObjtype() == eObjectType_PopUp)
		{
			PopUp* p = reinterpret_cast<PopUp*>(it);
			if (p->name == ePopup_close)
			{
				p->Render(pGraphics);
			}

		}
	}
}

void ScriptScene::Release()
{

}

void ScriptScene::printChoice(Gdiplus::Graphics* pGraphics)
{
	// ���� �׸� ���
	StaticObject* ScriptChoice = new StaticObject();
	ScriptChoice->setObjtype(eObjectType_None);
	ScriptChoice->setAssetFileName(TEXT("script_scene_choice.png"));
	ScriptChoice->setImgRC(Rect(0, 0, 1000, 248));
	ScriptChoice->setViewRC(Rect(355, 412, 1000, 248));

	auto pImg = (AssetManager::GetInstance().GetImage(ScriptChoice->getAssetFileName())).lock();

	pGraphics->DrawImage(pImg.get(), ScriptChoice->getViewRC(), ScriptChoice->getImgRC().X, ScriptChoice->getImgRC().Y, ScriptChoice->getImgRC().Width, ScriptChoice->getImgRC().Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	// ���� ��� 390 418
	Gdiplus::Font F(L"Arial", 6, FontStyleBold, UnitMillimeter);

	Gdiplus::PointF P1(ScriptChoice->getViewRC().X + 20, ScriptChoice->getViewRC().Y + 25);

	Gdiplus::SolidBrush B1(Color(13, 48, 119));

	wstring tempTex = L"��..������ ���Ƴ����� �� ����̵��� ��������� ���÷� ���� ��ΰ� ���������ž�..\n���� ��� �ؾ� ������?";

	// TODO. ���߿� ��¥ ��ġ�� �ٲ��ֱ�
	pGraphics->DrawString(tempTex.c_str(), -1, &F, P1, &B1);

	Gdiplus::PointF P2(ScriptChoice->getViewRC().X + 115, ScriptChoice->getViewRC().Y + 110);
	Gdiplus::SolidBrush B2(Color(76, 40, 113));

	wstring tempCho = L"��������� ���ÿ� �˸���.\n\n\n��������� ���÷� ���ϴ� [�ɱ�] ������� �����Ѵ�.";

	pGraphics->DrawString(tempCho.c_str(), -1, &F, P2, &B2);
}

void ScriptScene::printGameResult(Gdiplus::Graphics* pGraphics)
{
	//Gdiplus::Font F(L"Arial", 5, FontStyleBold, UnitMillimeter);

	//Gdiplus::PointF P1(45, 125);

	//Gdiplus::SolidBrush B1(Color(13, 48, 119));

	//wstring tempTex = L"��� : ";
	//if (GameManager::GetInstance().IsWin)
	//{
	//	tempTex += L"�¸�";
	//}
	//else
	//{
	//	tempTex += L"�й�";
	//}

	//pGraphics->DrawString(tempTex.c_str(), -1, &F, P1, &B1);
}