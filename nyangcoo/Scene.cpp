#include "pch.h"
#include "Scene.h"

void Scene::Init()
{
	for (auto& it : infoObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		obj->Init();

		// 이펙트일 경우 애니메이션이 실행되도록 초기화
		if (obj->getObjtype() == eObjectType_Effect)
		{
			obj->setEnable(true);
		}
	}
}

void Scene::Update(float Delta)
{
	for (auto& it : infoObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		// 플레이어일 경우
		if (obj->getObjtype() == eObjectType_Player || obj->getObjtype() == eObjectType_Character || obj->getObjtype() == eObjectType_Enemy)
		{
			Character* player = reinterpret_cast<Character*>(obj);
			player->Update(Delta);
		}
		else
		{
			obj->Update(Delta);
		}
	}

	for (auto& it : infoStaticObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if (obj->getObjtype() == eObjectType_PlayerSkillBtn)
		{
			PlayerSkillBtn* playerSkillBtn = reinterpret_cast<PlayerSkillBtn*>(obj);
			playerSkillBtn->Update(Delta);
		}
		else if (obj->getObjtype() == eObjectType_Btn)
		{
			Btn* btn = reinterpret_cast<Btn*>(obj);

			if (btn->getId() == ePlayerUpgradeBtn)
			{
				obj->setX(GameManager::GetInstance().CommandPlayer->getX() - 75);
				obj->setY(GameManager::GetInstance().CommandPlayer->getY() - GameManager::GetInstance().CommandPlayer->AniUnits[GameManager::GetInstance().CommandPlayer->curState][0].Height - 100);
			}
		}
		else
		{
			obj->Update(Delta);
		}
	}
}

void Scene::Render(Gdiplus::Graphics* pGraphics)
{
	if (pGraphics == nullptr) return;

	for (auto& it : infoStaticObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if ((this->name == "Scene_LoadGame" || this->name == "Scene_SaveGame" || this->name == "Scene_Script") && obj->getObjtype() == eObjectType_PopUp)
		{
			PopUp* popUp = reinterpret_cast<PopUp*>(obj);
			if (popUp->name == ePopup_close)
			{
			}
			else
			{
				obj->Render(pGraphics);
			}
		}
		else
		{
			obj->Render(pGraphics);
		}
	}

	for (auto& it : infoObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		if (obj->getObjtype() == eObjectType_Player || obj->getObjtype() == eObjectType_Character || obj->getObjtype() == eObjectType_Enemy)
		{
			Character* character = reinterpret_cast<Character*>(obj);
			character->Render(pGraphics);
		}
		else
		{
			obj->Render(pGraphics);
		}
	}

	for (auto& it : infoUIObj)
	{
		auto obj = it.second;

		if (obj == nullptr) continue;

		obj->Render(pGraphics);
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

multimap<int, Object*> Scene::getInfoObj()
{
	return infoObj;
}

void Scene::setInfoObj(multimap<int, Object*> _infoObj)
{
	infoObj = _infoObj;
}

void Scene::addToInfoObj(Object* _object)
{
	int zOrder = eLayer_Character;
	
	if (_object->getObjtype() == eObjectType_Effect)
	{
		zOrder = eLayer_Effect;
	}

	infoObj.insert(pair<int, Object*>(zOrder, _object));
}

multimap<int, StaticObject*> Scene::getInfoStaticObj()
{
	return infoStaticObj;
}

void Scene::setInfoStaticObj(multimap<int, StaticObject*> _infoStaticObj)
{
	infoStaticObj = _infoStaticObj;
}

multimap<int, StaticObject*> Scene::getInfoUIObj()
{
	return infoUIObj;
}

void Scene::setInfoUIObj(multimap<int, StaticObject*> _infoUIObj)
{
	infoUIObj = _infoUIObj;
}
