#include "pch.h"
#include "PlayerGraphicsComponent.h"

void PlayerGraphicsComponent::update(Object* obj, float Delta)
{
	PlayerDeltaA += Delta;

	if (PlayerDeltaA > AniDelta)
	{
		if (AniUnits.size() == AniFrameSize)
		{
			if (obj->Enable == false && AniFrameCnt >= AniUnits.size() - 1)
			{
				AniFrameCnt = 0;
				obj->Visible = false;

				return;
			}

			PlayerDeltaA = 0;
			AniFrameCnt = AniFrameCnt >= AniUnits.size() - 1 ? 0 : AniFrameCnt + 1;
		}
	}
}

void PlayerGraphicsComponent::render(Object* obj, Gdiplus::Graphics* pGraphics)
{
	if (obj == nullptr) return;
	if (pGraphics == nullptr) return;

	//프레임 확인용 코드. 출력 원하지 않을 경우 pch에서 define 부분을 주석처리.
#if defined FRAME_DEBUG
	SolidBrush br(Color(255, 0, 0, 0));
	CString temp;
	temp.Format(TEXT("%d"), (int)PlayerDeltaA);
	Gdiplus::Font font(&FontFamily(L"Arial"), 12);
	pGraphics->DrawString(temp, -1, &font, PointF(0, 100), &br);
#endif

	if (obj->Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(obj->AssetFileName)).lock();

	int displayX = obj->x - AniUnitWidth / 2;
	int displayY = obj->y - AniUnitHeight;

	Rect Dst(displayX, displayY, AniUnitWidth, AniUnitHeight);
	Rect unitDst(0, 0, AniUnitWidth, AniUnitHeight);

	//assert(AniUnits.size() > AniFrameCnt);
	Bitmap bm(AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, PixelFormat32bppARGB);
	Graphics test(&bm);
	test.DrawImage(pImg.get(), unitDst, AniUnits[AniFrameCnt].X, AniUnits[AniFrameCnt].Y, AniUnits[AniFrameCnt].Width, AniUnits[AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);

	if (obj->bleft == false)
		bm.RotateFlip(Rotate180FlipY);

	pGraphics->DrawImage(&bm, Dst);
}

void PlayerGraphicsComponent::setAniUnitSize(float width, float height)
{
	AniUnitWidth = width;
	AniUnitHeight = height;
}

void PlayerGraphicsComponent::setAniFrameCnt(int frameNum)
{
	//AniFrameCnt = 0;
	AniFrameSize = frameNum;
}

void PlayerGraphicsComponent::setAniDelta(float delta)
{
	AniDelta = delta;
}

void PlayerGraphicsComponent::Init(float width, float height, int frameNum, float delta, int rownum, int imgNumPerLine)
{
	PlayerDeltaA = 0;

	InitParams(width, height, frameNum, delta, rownum, imgNumPerLine);
}

void PlayerGraphicsComponent::InitParams(float width, float height, int frameNum, float delta, int rownum, int imgNumPerLine)
{
	CriticalSec a;
	setAniUnitSize(width, height);
	setAniFrameCnt(frameNum);
	setAniDelta(delta);

	InitAniUnits(rownum, imgNumPerLine);
}

void PlayerGraphicsComponent::InitAniUnits(int rownum, int imgNumPerLine)
{
	AniUnits.clear();

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
