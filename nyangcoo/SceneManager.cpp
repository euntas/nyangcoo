#include "pch.h"
#include "SceneManager.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager cm;
	return cm;
}

SceneManager::SceneManager()
	: CurScene(nullptr), CameraPt(0, 0)
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

	ScriptScene* scriptScene = new ScriptScene();
	mScene.emplace_back(scriptScene);
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
		if (it == nullptr) continue;

		Rect tempRC(it->x, it->y, it->ImgRC.Width, it->ImgRC.Height);
		if (it->Objtype == eObjectType_Btn && tempRC.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->SendLButtonDown();
			
		}
		else if (it->Objtype == eObjectType_PopUp)
		{
			PopUp* pb = reinterpret_cast<PopUp*>(it);
			for (auto& pbit : pb->infoStaticObj)
			{
				if (pbit->Objtype == eObjectType_Btn && pbit->ViewRC.Contains(point.x, point.y) && pb->Visible)
				{
					Btn* o = reinterpret_cast<Btn*>(pbit);
					o->SendLButtonDown();
				}
			}
		}
		else if (it->Objtype == eObjectType_MakeCharacterBtn)
		{
			MakeCharacterBtn* mcb = reinterpret_cast<MakeCharacterBtn*>(it);

			Rect tempRC(mcb->x, mcb->y, mcb->ImgRC.Width, mcb->ImgRC.Height);
			if (tempRC.Contains(point.x, point.y))
			{
				mcb->SendLButtonDown();
			}
		}
		else if (it->Objtype == eObjectType_UpgradeCharacterBtn)
		{
			UpgradeCharacterBtn* ucb = reinterpret_cast<UpgradeCharacterBtn*>(it);

			Rect tempRC(ucb->x, ucb->y, ucb->ImgRC.Width, ucb->ImgRC.Height);
			if (tempRC.Contains(point.x, point.y))
			{
				ucb->SendLButtonDown();
			}
		}
	}
}

void SceneManager::SendMouseMove(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->infoStaticObj)
	{
		if (it == nullptr) continue;

		Rect tempRC(it->x, it->y, it->ViewRC.Width, it->ViewRC.Height);
		if (it->Objtype == eObjectType_Btn && tempRC.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->ViewRC.Width = o->ImgRC.Width + 50;
			o->ViewRC.Height = o->ImgRC.Height + 50;
			printf("point : %d, %d\n", point.x, point.y);
		}
		else if (it->Objtype == eObjectType_Btn)
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->ViewRC.Width = o->ImgRC.Width;
			o->ViewRC.Height = o->ImgRC.Height;
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

void SceneManager::SendKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (CurScene->Name == "Scene_Game")
	{
		GameScene* gs = reinterpret_cast<GameScene*>(GetCurScene());

		int moveX = 10;
		bool flag = false;

		if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		{
			flag = true;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		{
			flag = true;
			moveX *= -1;
		}

		// 키가 눌린 경우 배경화면과 캐릭터의 x값을 변경해준다.
		if (flag)
		{
			StaticObject* Bg = GameManager::GetInstance().curStage->bg;
			int tempx = Bg->ImgRC.X + moveX;
			if (tempx >= 0 && tempx <= Bg->ImgRC.Width - Bg->ViewRC.Width)
			{
				Bg->ImgRC.X += moveX;

				for (auto& it : gs->infoObj)
				{
					it->x -= moveX;
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		for (auto& it : GetCurScene()->infoStaticObj)
		{
			if (it->Objtype == eObjectType_PopUp)
			{
				it->Visible = !it->Visible;
			}
		}
	}
}
