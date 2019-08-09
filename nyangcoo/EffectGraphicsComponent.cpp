#include "pch.h"
#include "EffectGraphicsComponent.h"

void EffectGraphicsComponent::update(Object* obj, float Delta)
{
	EffectDeltaA += Delta;

	if (obj->Enable == true && EffectDeltaA > AniDelta)
	{
		EffectDeltaA = 0;
		++AniFrameCnt;
		if (AniFrameCnt > AniUnits.size() - 1)
		{
			AniFrameCnt = 0;
			obj->Enable = false;
		}
	}
}

void EffectGraphicsComponent::render(Object* obj, Gdiplus::Graphics* pGraphics)
{
	if (obj->Enable)
	{
		auto pImg = (AssetManager::GetInstance().GetImage(obj->AssetFileName)).lock();

		int displayX = obj->x - AniUnitWidth / 2;
		int displayY = obj->y - AniUnitHeight / 2;

		Rect Dst(displayX, displayY, AniUnitWidth, AniUnitHeight);

		pGraphics->DrawImage(pImg.get(), Dst, AniUnits[AniFrameCnt].X, AniUnits[AniFrameCnt].Y, AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void EffectGraphicsComponent::setAniUnitSize(float width, float height)
{
	AniUnitWidth = width;
	AniUnitHeight = height;
}

void EffectGraphicsComponent::setAniFrameCnt(int frameNum)
{
	AniFrameSize = frameNum;
}

void EffectGraphicsComponent::setAniDelta(float delta)
{
	AniDelta = delta;
}

void EffectGraphicsComponent::Init(float width, float height, int frameNum, float delta, int rownum, int imgNumPerLine)
{
	EffectDeltaA = 0;

	setAniUnitSize(width, height);
	setAniFrameCnt(frameNum);
	setAniDelta(delta);

	InitAniUnits(rownum, imgNumPerLine);
}

void EffectGraphicsComponent::InitAniUnits(int rownum, int imgNumPerLine)
{
	int cnt = 0;
	for (int i = 0; i < rownum; ++i)
	{
		for (int j = 0; j < imgNumPerLine; ++j)
		{
			if (cnt >= AniFrameSize) return;

			int x = j * AniUnitWidth;
			int y = i * AniUnitHeight;

			AniUnits.emplace_back(Rect(x, y, AniUnitWidth, AniUnitHeight));
			cnt++;
		}
	}
}