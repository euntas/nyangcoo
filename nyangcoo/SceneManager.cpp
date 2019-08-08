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
	StartScene* startScene = new StartScene();
	mScene.emplace_back(startScene);
	
	GameScene* gameScene = new GameScene();
	mScene.emplace_back(gameScene);

	LoadGameScene* loadgameScene = new LoadGameScene();
	mScene.emplace_back(loadgameScene);
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

	
	// UI 그림 출력 . TODO. Scene 안의 render로 옮겨야 함
	for (auto& it : CurScene->infoStaticObj)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();

		if (it->Objtype == eObjectType_BGImage) // 배경 그림
		{
			pGraphics->DrawImage(pImg.get(), ViewRC, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
		else // 그 외 그림
		{
			Rect tempRC(it->x, it->y, it->rc.Width, it->rc.Height);
			pGraphics->DrawImage(pImg.get(), tempRC, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}

	CurScene->Render(pGraphics);
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
		Rect tempRC(it->x, it->y, it->rc.Width, it->rc.Height);
		if (it->Objtype == eObjectType_Btn && tempRC.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->SendLButtonDown();
		}
	}
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;

	CurScene->Update(Delta);
}