#include "pch.h"
#include "Scene.h"

void Scene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// ����Ʈ�� ��� �ִϸ��̼��� ����ǵ��� �ʱ�ȭ
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

		// �÷��̾��� ���
		if (it->Objtype == eObjectType_Player)
		{
			it->Update(Delta);
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

		it->Render(pGraphics);
	}

	for (auto& it : infoUIObj)
	{
		if (it == nullptr) continue;

		it->Render(pGraphics);
	}
}

void Scene::Release()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// �÷��̾��� ���
		if (it->Objtype == eObjectType_Player)
		{
			Player* p = reinterpret_cast<Player*>(it);
			p->Release();
		}
		else if (it->Objtype == eObjectType_Enemy)
		{
			Enemy* e = reinterpret_cast<Enemy*>(it);
			e->Release();
		}
		else
		{
			it->Release();
		}
	}
}
