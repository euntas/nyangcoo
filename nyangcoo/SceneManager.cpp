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

	SaveGameScene* savegameScene = new SaveGameScene();
	mScene.emplace_back(savegameScene);

	ChapterSelectScene* chapterselectScene = new ChapterSelectScene();
	mScene.emplace_back(chapterselectScene);

	CookieSelectScene* cookieselectScene = new CookieSelectScene();
	mScene.emplace_back(cookieselectScene);

	ScriptScene* scriptScene = new ScriptScene();
	mScene.emplace_back(scriptScene);


	sndPlaySound(L"Asset\\MainSound.wav", SND_ASYNC | SND_LOOP);
}

Scene* SceneManager::GetSceneByName(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->getName().CompareNoCase(pName))
		{
			return it;
		}
	}

	return nullptr;
}

void SceneManager::LoadScene(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->getName().CompareNoCase(pName))
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

	for (auto& it : CurScene->getInfoStaticObj())
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		Rect tempRC(obj->getX(), obj->getY(), obj->getImgRC().Width, obj->getImgRC().Height);
		if (obj->getObjtype() == eObjectType_Btn && tempRC.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(obj);
			o->SendLButtonDown();
			
		}
		else if (obj->getObjtype() == eObjectType_PopUp)
		{
			PopUp* pb = reinterpret_cast<PopUp*>(obj);
			for (auto& pbit : pb->infoStaticObj)
			{
				if (pbit->getObjtype() == eObjectType_Btn && pbit->getViewRC().Contains(point.x, point.y) && pb->getVisible())
				{
					Btn* o = reinterpret_cast<Btn*>(pbit);
					o->SendLButtonDown();
				}
			}
		}
		else if (obj->getObjtype() == eObjectType_MakeCharacterBtn)
		{
			MakeCharacterBtn* mcb = reinterpret_cast<MakeCharacterBtn*>(obj);

			Rect tempRC(mcb->getX(), mcb->getY(), mcb->getImgRC().Width, mcb->getImgRC().Height);
			if (tempRC.Contains(point.x, point.y))
			{
				mcb->SendLButtonDown();
			}
		}
		else if (obj->getObjtype() == eObjectType_UpgradeCharacterBtn)
		{
			UpgradeCharacterBtn* ucb = reinterpret_cast<UpgradeCharacterBtn*>(obj);

			Rect tempRC(ucb->getX(), ucb->getY(), ucb->getImgRC().Width, ucb->getImgRC().Height);
			if (tempRC.Contains(point.x, point.y))
			{
				ucb->SendLButtonDown();
			}
		}
		else if (obj->getObjtype() == eObjectType_PlayerSkillBtn)
		{
			PlayerSkillBtn* psb = reinterpret_cast<PlayerSkillBtn*>(obj);

			Rect tempRC(psb->btnImg->getX(), psb->btnImg->getY(), psb->btnImg->getImgRC().Width, psb->btnImg->getImgRC().Height);
			if (tempRC.Contains(point.x, point.y))
			{
				psb->SendLButtonDown();
			}
		}
	}

	for (auto& it : CurScene->getInfoUIObj())
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if (obj->getObjtype() == eObjectType_PopUp)
		{
			PopUp* pb = reinterpret_cast<PopUp*>(obj);
			for (auto& pbit : pb->infoStaticObj)
			{
				if (pbit->getObjtype() == eObjectType_Btn && pbit->getViewRC().Contains(point.x, point.y) && pb->getVisible())
				{
					Btn* o = reinterpret_cast<Btn*>(pbit);
					o->SendLButtonDown();
				}
			}
		}
	}
}

void SceneManager::SendMouseMove(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->getInfoStaticObj())
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		Rect tempRC(obj->getX(), obj->getY(), obj->getViewRC().Width, obj->getViewRC().Height);
		if (obj->getObjtype() == eObjectType_Btn && tempRC.Contains(point.x, point.y))
		{
			Btn* o = reinterpret_cast<Btn*>(obj);
			o->setViewRC(Rect(o->getViewRC().X, o->getViewRC().Y, o->getImgRC().Width + 50, o->getImgRC().Height + 50));
			printf("point : %d, %d\n", point.x, point.y);
		}
		else if (obj->getObjtype() == eObjectType_Btn)
		{
			Btn* o = reinterpret_cast<Btn*>(obj);
			o->setViewRC(Rect(o->getViewRC().X, o->getViewRC().Y, o->getImgRC().Width, o->getImgRC().Height));
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
	if (CurScene->getName() == "Scene_Game")
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
			int tempx = Bg->getImgRC().X + moveX;
			if (tempx >= 0 && tempx <= Bg->getImgRC().Width - Bg->getViewRC().Width)
			{
				Rect tempRC = Bg->getImgRC();
				tempRC.X += moveX;
				Bg->setImgRC(tempRC);

				for (auto& it : gs->getInfoObj())
				{
					auto obj = it.second;

					if (obj == nullptr) continue;

					obj->setX(obj->getX() - moveX);
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		for (auto& it : GetCurScene()->getInfoStaticObj())
		{
			auto obj = it.second;

			if (obj == nullptr) continue;

			PopUp* popup = reinterpret_cast<PopUp*>(obj);

			if (obj->getObjtype() == eObjectType_PopUp && popup->name != ePopup_result)
			{
				obj->setVisible(!obj->getVisible());
			}
		}

		for (auto& it : GetCurScene()->getInfoUIObj())
		{
			auto obj = it.second;

			if (obj == nullptr) continue;

			PopUp* popup = reinterpret_cast<PopUp*>(obj);

			if (obj->getObjtype() == eObjectType_PopUp && popup->name != ePopup_result)
			{
				obj->setVisible(!obj->getVisible());
			}
		}
	}
}
