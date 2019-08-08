#include "pch.h"
#include "Scene.h"

void Scene::Init()
{

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
	}
}

void Scene::Render(Gdiplus::Graphics* pGraphics)
{
	if (this == nullptr) return;
	if (pGraphics == nullptr) return;

	for (auto& it : infoStaticObj)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		auto pImg = (AssetManager::GetInstance().GetImage(it->AssetFileName)).lock();

		if (it->Objtype == eObjectType_BGImage) // ��� �׸�
		{
			pGraphics->DrawImage(pImg.get(), SceneManager::GetInstance().ViewRC, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
		else // �� �� �׸�
		{
			Rect tempRC(it->x, it->y, it->rc.Width, it->rc.Height);
			pGraphics->DrawImage(pImg.get(), tempRC, it->rc.X, it->rc.Y, it->rc.Width, it->rc.Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);
		}
	}

	for (auto& it : infoObj)
	{
		if (it == nullptr) continue;

		// �÷��̾��� ���
		if (it->Objtype == eObjectType_Player)
		{
			it->Render(pGraphics);
		}
	}
}

void Scene::Release()
{

}
