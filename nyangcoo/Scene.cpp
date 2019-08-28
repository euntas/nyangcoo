#include "pch.h"
#include "Scene.h"

void Scene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		it->Init();

		// 이펙트일 경우 애니메이션이 실행되도록 초기화
		if (it->getObjtype() == eObjectType_Effect)
		{
			it->setEnable(true);
		}
	}
}

void Scene::Update(float Delta)
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// 플레이어일 경우
		if (it->getObjtype() == eObjectType_Player || it->getObjtype() == eObjectType_Character || it->getObjtype() == eObjectType_Enemy)
		{
			Character* p = reinterpret_cast<Character*>(it);
			p->Update(Delta);
		}
		else
		{
			it->Update(Delta);
		}
	}

	for (auto& it : infoStaticObj)
	{
		if (it == nullptr) continue;

		if (it->getObjtype() == eObjectType_PlayerSkillBtn)
		{
			PlayerSkillBtn* psb = reinterpret_cast<PlayerSkillBtn*>(it);
			psb->Update(Delta);
		}
		else if (it->getObjtype() == eObjectType_Btn)
		{
			Btn* b = reinterpret_cast<Btn*>(it);

			if (b->ID == ePlayerUpgradeBtn)
			{
				GameScene* gs = reinterpret_cast<GameScene*>(SceneManager::GetInstance().GetCurScene());

				it->setX(GameManager::GetInstance().CommandPlayer->getX() - 75);
				it->setY(GameManager::GetInstance().CommandPlayer->getY() - GameManager::GetInstance().CommandPlayer->AniUnits[GameManager::GetInstance().CommandPlayer->curState][0].Height - 100);
			}
		}
		else
		{
			it->Update(Delta);
		}
	}
}

void Scene::Render(Gdiplus::Graphics* pGraphics)
{
	if (this == nullptr) return;
	if (pGraphics == nullptr) return;

	for (auto& it : infoStaticObj)
	{
		if (it == nullptr) continue;

		if ((this->name == "Scene_LoadGame" || this->name == "Scene_SaveGame" || this->name == "Scene_Script") && it->getObjtype() == eObjectType_PopUp)
		{
			PopUp* p = reinterpret_cast<PopUp*>(it);
			if (p->name == ePopup_close)
			{
			}
			else
			{
				it->Render(pGraphics);
			}
		}
		else
		{
			it->Render(pGraphics);
		}
	}

	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		if (it->getObjtype() == eObjectType_Player || it->getObjtype() == eObjectType_Character || it->getObjtype() == eObjectType_Enemy)
		{
			Character* p = reinterpret_cast<Character*>(it);
			p->Render(pGraphics);
		}
		else
		{
			it->Render(pGraphics);
		}
	}

	for (auto& it : infoUIObj)
	{
		if (it == nullptr) continue;

		it->Render(pGraphics);
	}
}

void Scene::Release()
{
	//for (auto it = infoObj.begin(); it != infoObj.end(); ++it)
	//{
	//	if ((*it) == nullptr) continue;

	//	// 플레이어일 경우
	//	if ((*it)->Objtype == eObjectType_Player)
	//	{
	//		Player* p = reinterpret_cast<Player*>(*it);
	//		if (p->CheckDestroy())
	//		{
	//			it = infoObj.erase(it);
	//		}
	//	}
	//	else if ((*it)->Objtype == eObjectType_Enemy)
	//	{
	//		Enemy* e = reinterpret_cast<Enemy*>(*it);
	//		if (e->CheckDestroy())
	//		{
	//			it = infoObj.erase(it);
	//		}
	//	}
	//	else
	//	{
	//		//it->Release();
	//	}
	//}
}

void Scene::ClearAll()
{
	infoObj.clear();
	infoStaticObj.clear();
	infoUIObj.clear();
}

bool Scene::getBLoop()
{
	return bLoop;
}

void Scene::setBLoop(bool _bLoop)
{
	bLoop = _bLoop;
}

CString Scene::getName()
{
	return name;
}

void Scene::setName(CString _name)
{
	name = _name;
}

vector<Object*> Scene::getInfoObj()
{
	return infoObj;
}

void Scene::setInfoObj(vector<Object*> _infoObj)
{
	infoObj = _infoObj;
}

void Scene::addToInfoObj(Object* _object)
{
	infoObj.emplace_back(_object);
}

vector<StaticObject*> Scene::getInfoStaticObj()
{
	return infoStaticObj;
}

void Scene::setInfoStaticObj(vector<StaticObject*> _infoStaticObj)
{
	infoStaticObj = _infoStaticObj;
}

vector<StaticObject*> Scene::getInfoUIObj()
{
	return infoUIObj;
}

void Scene::setInfoUIObj(vector<StaticObject*> _infoUIObj)
{
	infoUIObj = _infoUIObj;
}
