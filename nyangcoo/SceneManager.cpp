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

	ChapterSelectScene* chapterselectScene = new ChapterSelectScene();
	mScene.emplace_back(chapterselectScene);

	CookieSelectScene* cookieselectScene = new CookieSelectScene();
	mScene.emplace_back(cookieselectScene);
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

void SceneManager::Init()
{
	if (CurScene == nullptr) return;

	CurScene->Init();
}

void SceneManager::Release()
{
	if (CurScene == nullptr) return;

	CurScene->Release();
}