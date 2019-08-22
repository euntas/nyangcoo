#include "pch.h"
#include "Scene.h"

void Scene::Init()
{
	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		it->Init();

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
		if (it->Objtype == eObjectType_Player || it->Objtype == eObjectType_Character || it->Objtype == eObjectType_Enemy)
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

		if (it->Objtype == eObjectType_PlayerSkillBtn)
		{
			PlayerSkillBtn* psb = reinterpret_cast<PlayerSkillBtn*>(it);
			psb->Update(Delta);
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

		if ((this->Name == "Scene_LoadGame" || this->Name == "Scene_SaveGame" || this->Name == "Scene_Script") && it->Objtype == eObjectType_PopUp)
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

		if (it->Objtype == eObjectType_Player || it->Objtype == eObjectType_Character || it->Objtype == eObjectType_Enemy)
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

	//	// �÷��̾��� ���
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
