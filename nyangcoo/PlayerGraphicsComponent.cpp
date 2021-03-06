#include "pch.h"
#include "PlayerGraphicsComponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(Object* obj)
{
	parentObj = obj;

	Init();
	InitParams();
}

PlayerGraphicsComponent::PlayerGraphicsComponent(Character* obj)
{
	parentObj = obj;

	Init();
	InitParams();
}

void PlayerGraphicsComponent::update(float Delta)
{
	CriticalSec a;

	PlayerDeltaA += Delta;

	if (parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
	{
		Character* p = reinterpret_cast<Character*>(parentObj);

		if (PlayerDeltaA > p->frameDelta[p->curState])
		{
			//if (p->AniUnits[p->curState].size() == p->frameNum[p->curState])
			//{
				if (p->Enable == false && AniFrameCnt >= p->AniUnits[p->curState].size() - 1)
				{
					AniFrameCnt = 0;
					parentObj->Visible = false;

					return;
				}

				PlayerDeltaA = 0;
				AniFrameCnt = AniFrameCnt >= p->AniUnits[p->curState].size() - 1 ? 0 : AniFrameCnt + 1;
			//}
		}
	}

	
}

void PlayerGraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	if (parentObj == nullptr) return;
	if (pGraphics == nullptr) return;

	//프레임 확인용 코드. 출력 원하지 않을 경우 pch에서 define 부분을 주석처리.
#if defined FRAME_DEBUG
	SolidBrush br(Color(255, 0, 0, 0));
	CString temp;
	temp.Format(TEXT("%d"), (int)PlayerDeltaA);
	Gdiplus::Font font(&FontFamily(L"Arial"), 12);
	pGraphics->DrawString(temp, -1, &font, PointF(0, 100), &br);
#endif

	if (parentObj->Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(parentObj->AssetFileName)).lock();

	if (parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
	{
		Character* p = reinterpret_cast<Character*>(parentObj);

		int displayX = parentObj->x - p->frameWidth[p->curState] / 2;
		int displayY = parentObj->y - p->frameHeight[p->curState];

		Rect Dst(displayX, displayY, p->frameWidth[p->curState], p->frameHeight[p->curState]);
		Rect unitDst(0, 0, p->frameWidth[p->curState], p->frameHeight[p->curState]);

		Bitmap bm(p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, PixelFormat32bppARGB);
		Graphics test(&bm);
		test.DrawImage(pImg.get(), unitDst, p->AniUnits[p->curState][AniFrameCnt].X, p->AniUnits[p->curState][AniFrameCnt].Y, p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

		if (parentObj->bleft == false)
			bm.RotateFlip(Rotate180FlipY);

		pGraphics->DrawImage(&bm, Dst);
	}
}

void PlayerGraphicsComponent::Init()
{
	PlayerDeltaA = 0;
}

void PlayerGraphicsComponent::InitParams()
{
	CriticalSec a;

	InitAniUnits();
}

void PlayerGraphicsComponent::InitAniUnits()
{
	CriticalSec a;

	if (parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
	{
		Character* p = reinterpret_cast<Character*>(parentObj);

		for (int state = 0; state < eState_Cnt; state++)
		{
			p->AniUnits[state].clear();

			int rownum = p->spriteRowNum[state];
			int imgNumPerLine = p->imgNumPerLine[state];

			int cnt = 0;
			for (int i = 0; i < rownum; ++i)
			{
				for (int j = 0; j < imgNumPerLine; ++j)
				{
					int x = j * p->frameWidth[state];
					int y = i * p->frameHeight[state];

					p->AniUnits[state].emplace_back(Rect(x, y, p->frameWidth[state], p->frameHeight[state]));
					cnt++;
				}
			}
		}
	}
}
