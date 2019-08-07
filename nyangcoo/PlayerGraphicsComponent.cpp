#include "pch.h"
#include "PlayerGraphicsComponent.h"

void PlayerGraphicsComponent::update(Object* obj, float Delta)
{
	PlayerDeltaA += Delta;

	if (PlayerDeltaA > AniDelta)
	{
		PlayerDeltaA = 0;
		++AniFrameCnt;
		if (AniFrameCnt > AniUnits.size() - 1)
			AniFrameCnt = 0;
	}
}

void PlayerGraphicsComponent::render(Object* obj, Gdiplus::Graphics* pGraphics)
{
	auto pImg = (AssetManager::GetInstance().GetImage(obj->AssetFileName)).lock();

	Rect Dst(50, 400, AniUnitWidth, AniUnitHeight);

	pGraphics->DrawImage(pImg.get(), Dst, AniUnits[AniFrameCnt].X, AniUnits[AniFrameCnt].Y, AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}

void PlayerGraphicsComponent::setAniUnitSize(float width, float height)
{
	AniUnitWidth = width;
	AniUnitHeight = height;
}

void PlayerGraphicsComponent::setAniFrameCnt(int frameNum)
{
	AniFrameSize = frameNum;
}

void PlayerGraphicsComponent::setAniDelta(float delta)
{
	AniDelta = delta;
}

// TODO. 추후 xml 파일을 읽어서 초기화해주도록 바꾸어야 함
void PlayerGraphicsComponent::Init(float width, float height, int frameNum, float delta)
{
	setAniUnitSize(width, height);
	setAniFrameCnt(frameNum);
	setAniDelta(delta);

	InitAniUnits();
}

void PlayerGraphicsComponent::InitAniUnits()
{
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < AniFrameSize; ++j)
		{
			int x = j * AniUnitWidth;
			int y = i * AniUnitHeight;
			/*if (i == 3 && j == 5)
				break;*/
			AniUnits.emplace_back(Rect(x, y, AniUnitWidth, AniUnitHeight));
		}
	}
}
