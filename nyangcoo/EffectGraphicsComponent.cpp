#include "pch.h"
#include "EffectGraphicsComponent.h"

EffectGraphicsComponent::EffectGraphicsComponent(Object* obj)
{
	parentObj = obj;

	Init();
}

EffectGraphicsComponent::EffectGraphicsComponent(Effect* obj)
{
	parentObj = obj;

	Init();

	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	InitAniUnits(ef->spriteRowNum, ef->imgNumPerLine);
}

void EffectGraphicsComponent::update(float Delta)
{
	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	EffectDeltaA += Delta;

	if (ef->getEnable() == true && EffectDeltaA > ef->frameDelta)
	{
		EffectDeltaA = 0;
		++AniFrameCnt;
		if (AniFrameCnt >= AniUnits.size() - 1)
		{
			AniFrameCnt = 0;
			ef->setEnable(false);
			ef->setVisible(false);
		}
	}
}

void EffectGraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	if (ef->getVisible() == false)
		return;

	if (ef->getEnable())
	{
		auto pImg = (AssetManager::GetInstance().GetImage(ef->getAssetFileName())).lock();

		int displayX = ef->getX() - ef->frameWidth / 2;
		int displayY = ef->getY() - ef->frameHeight / 2;

		Rect Dst(displayX, displayY, ef->frameWidth, ef->frameHeight);

		pGraphics->DrawImage(pImg.get(), Dst, AniUnits[AniFrameCnt].X, AniUnits[AniFrameCnt].Y, AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void EffectGraphicsComponent::Init()
{
	EffectDeltaA = 0;
}

void EffectGraphicsComponent::InitAniUnits(int rownum, int imgNumPerLine)
{
	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	int cnt = 0;
	for (int i = 0; i < rownum; ++i)
	{
		for (int j = 0; j < imgNumPerLine; ++j)
		{
			if (cnt >= ef->frameNum) return;

			int x = j * ef->frameWidth;
			int y = i * ef->frameHeight;

			AniUnits.emplace_back(Rect(x, y, ef->frameWidth, ef->frameHeight));

			cnt++;
		}
	}
}