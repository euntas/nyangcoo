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
	//������ Ȯ�ο� �ڵ�. ��� ������ ���� ��� pch���� define �κ��� �ּ�ó��.
#if defined FRAME_DEBUG
	SolidBrush br(Color(255, 0, 0, 0));
	CString temp;
	temp.Format(TEXT("%d"), (int)PlayerDeltaA);
	Gdiplus::Font font(&FontFamily(L"Arial"), 12);
	pGraphics->DrawString(temp, -1, &font, PointF(0, 100), &br);
#endif

	auto pImg = (AssetManager::GetInstance().GetImage(obj->AssetFileName)).lock();

	// TODO. xml���� �о�� ������ �ٲپ�� ��
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

// TODO. ���� xml ������ �о �ʱ�ȭ���ֵ��� �ٲپ�� ��
void PlayerGraphicsComponent::Init(float width, float height, int frameNum, float delta)
{
	PlayerDeltaA = 0;

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

			AniUnits.emplace_back(Rect(x, y, AniUnitWidth, AniUnitHeight));
		}
	}
}
