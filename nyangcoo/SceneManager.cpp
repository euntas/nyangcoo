#include "pch.h"
#include "SceneManager.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager cm;
	return cm;
}

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	LoginScene* loginScene = new LoginScene();
	mScene.emplace_back(loginScene);
	
	GameScene* gameScene = new GameScene();
	mScene.emplace_back(gameScene);
}

void SceneManager::LoadScene(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->Name.CompareNoCase(pName))
		{
			CurScene = it;
		}
	}

	//CurScene = nullptr;
}

void SceneManager::RenderScene(Graphics* pGraphics)
{
	if (CurScene == nullptr) return;
	if (pGraphics == nullptr) return;

	// TODO. Scene 별 배경그림 그리는 부분. 이 부분을 위한 함수를 따로 만들거나, 다른 이미지처럼 info에 넣는 방식으로 바꿔야 함.
	
	Rect Dst(0, 0, 2080, 2920);
	// 배경 그림 넣어주는 부분
	if (CurScene->Name == "Scene_Start")
	{
		LoginScene* ls = static_cast<LoginScene*>(CurScene);

		auto pBgImg = (AssetManager::GetInstance().GetImage(ls->bg->AssetFileName)).lock();
		pGraphics->DrawImage(pBgImg.get(), Dst, ls->bg->rc.X, ls->bg->rc.Y, ls->bg->rc.Width, ls->bg->rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
	else if (CurScene->Name == "Scene_Game")
	{
		GameScene* ls = static_cast<GameScene*>(CurScene);

		auto pBgImg = (AssetManager::GetInstance().GetImage(ls->bg->AssetFileName)).lock();
		pGraphics->DrawImage(pBgImg.get(), Dst, ls->bg->rc.X, ls->bg->rc.Y, ls->bg->rc.Width, ls->bg->rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}

	for (auto& it : CurScene->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();
		pGraphics->DrawImage(pImg.get(), it->rc, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->info)
	{
		if (it->Objtype == eObjectType_Btn && it->rc.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->SendLButtonDown();
		}
	}
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;

}