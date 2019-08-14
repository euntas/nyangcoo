#include "pch.h"
#include "Scene.h"

void Scene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		it->Init();

		// 이펙트일 경우 애니메이션이 실행되도록 초기화
		if (it->Objtype == eObjectType_Effect)
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
		if (it->Objtype == eObjectType_Player)
		{
			Player* p = reinterpret_cast<Player*>(it);
			p->Update(Delta);
		}
		else if (it->Objtype == eObjectType_Enemy)
		{
			Enemy* e = reinterpret_cast<Enemy*>(it);
			e->Update(Delta);
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

		it->Render(pGraphics);
	}

	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		if (it->Objtype == eObjectType_Player)
		{
			Player* p = reinterpret_cast<Player*>(it);
			p->Render(pGraphics);
		}
		else if (it->Objtype == eObjectType_Enemy)
		{
			Enemy* e = reinterpret_cast<Enemy*>(it);
			e->Render(pGraphics);
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
