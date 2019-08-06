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

	// UI 그림 출력
	for (auto& it : CurScene->infoStaticObj)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();

		if (it->Objtype == eObjectType_BGImage) // 배경 그림
		{
			Rect Dst(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN));
			pGraphics->DrawImage(pImg.get(), Dst, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
		else // 그 외 그림
		{
			pGraphics->DrawImage(pImg.get(), it->rc, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->infoStaticObj)
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