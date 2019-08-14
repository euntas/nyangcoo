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
}

void EffectGraphicsComponent::update(float Delta)
{
	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	EffectDeltaA += Delta;

	if (ef->Enable == true && EffectDeltaA > ef->frameDelta)
	{
		EffectDeltaA = 0;
		++AniFrameCnt;
		if (AniFrameCnt > AniUnits.size() - 1)
		{
			AniFrameCnt = 0;
			ef->Enable = false;
		}
	}
}

void EffectGraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	if (ef->Enable)
	{
		auto pImg = (AssetManager::GetInstance().GetImage(ef->AssetFileName)).lock();

		int displayX = ef->x - ef->frameWidth / 2;
		int displayY = ef->y - ef->frameHeight / 2;

		Rect Dst(displayX, displayY, ef->frameWidth, ef->frameHeight);

		pGraphics->DrawImage(pImg.get(), Dst, AniUnits[AniFrameCnt].X, AniUnits[AniFrameCnt].Y, AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void EffectGraphicsComponent::Init()
{
	EffectDeltaA = 0;

	Effect* ef = reinterpret_cast<Effect*>(parentObj);

	InitAniUnits(ef->spriteRowNum, ef->imgNumPerLine);
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