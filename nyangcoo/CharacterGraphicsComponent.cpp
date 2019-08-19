#include "pch.h"
#include "CharacterGraphicsComponent.h"

CharacterGraphicsComponent::CharacterGraphicsComponent(Object* obj)
{
	parentObj = obj;

	Init();
	InitParams();
}

CharacterGraphicsComponent::CharacterGraphicsComponent(Character* obj)
{
	parentObj = obj;

	Init();
	InitParams();
}

void CharacterGraphicsComponent::update(float Delta)
{
	PlayerDeltaA += Delta;

	if (parentObj->Objtype == eObjectType_Player || parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
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

void CharacterGraphicsComponent::render(Gdiplus::Graphics* pGraphics)
{
	if (parentObj == nullptr) return;
	if (pGraphics == nullptr) return;

	if (parentObj->Visible == false)
		return;

	auto pImg = (AssetManager::GetInstance().GetImage(parentObj->AssetFileName)).lock();

	if (parentObj->Objtype == eObjectType_Player || parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
	{
		Character* p = reinterpret_cast<Character*>(parentObj);

		int displayX = parentObj->x - p->frameWidth[p->curState] / 2;
		int displayY = parentObj->y - p->frameHeight[p->curState];

		// 범위 밖 (-300 ~ width + 300) 이면 그리지 않는다
		if (displayX < -300 || displayX > GameManager::GetInstance().curStage->bg->ViewRC.Width + 300)
			return;

		Rect Dst(displayX, displayY, p->frameWidth[p->curState], p->frameHeight[p->curState]);
		Rect unitDst(0, 0, p->frameWidth[p->curState], p->frameHeight[p->curState]);

		if (GameManager::GetInstance().IsGrayScale && SceneManager::GetInstance().GetCurScene()->Name == "Scene_Game")
		{
			//gray scale conversion:
			Gdiplus::ColorMatrix matrix =
			{
				.3f, .3f, .3f,   0,   0,
				.6f, .6f, .6f,   0,   0,
				.1f, .1f, .1f,   0,   0,
				0,   0,   0,   1,   0,
				0,   0,   0,   0,   1
			};

			Gdiplus::ImageAttributes attr;
			attr.SetColorMatrix(&matrix,
				Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

			Bitmap bm(p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, PixelFormat32bppARGB);
			Graphics test(&bm);
			test.DrawImage(pImg.get(), unitDst, p->AniUnits[p->curState][AniFrameCnt].X, p->AniUnits[p->curState][AniFrameCnt].Y, p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
				&attr, 0, nullptr);

			if (parentObj->bleft == false)
				bm.RotateFlip(Rotate180FlipY);

			pGraphics->DrawImage(&bm, Dst);
		}
		else
		{
			Bitmap bm(p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, PixelFormat32bppARGB);
			Graphics test(&bm);
			test.DrawImage(pImg.get(), unitDst, p->AniUnits[p->curState][AniFrameCnt].X, p->AniUnits[p->curState][AniFrameCnt].Y, p->AniUnits[p->curState][AniFrameCnt].Width, p->AniUnits[p->curState][AniFrameCnt].Height, Gdiplus::Unit::UnitPixel,
				nullptr, 0, nullptr);

			if (parentObj->bleft == false)
				bm.RotateFlip(Rotate180FlipY);

			pGraphics->DrawImage(&bm, Dst);
		}
	}
}

void CharacterGraphicsComponent::Init()
{
	PlayerDeltaA = 0;
}

void CharacterGraphicsComponent::ChangeMotion()
{
	PlayerDeltaA = 0;
	AniFrameCnt = 0;
}

void CharacterGraphicsComponent::InitParams()
{
	InitAniUnits();
}

void CharacterGraphicsComponent::InitAniUnits()
{
	if (parentObj->Objtype == eObjectType_Player || parentObj->Objtype == eObjectType_Character || parentObj->Objtype == eObjectType_Enemy)
	{
		Character* p = reinterpret_cast<Character*>(parentObj);

		for (int state = 0; state < eState_Cnt; state++)
		{
			//p->AniUnits[state].clear();

			int rownum = p->spriteRowNum[state];
			int imgNumPerLine = p->imgNumPerLine[state];
			p->AniUnits[state].resize(rownum * imgNumPerLine);

			int cnt = 0;
			for (int i = 0; i < rownum; ++i)
			{
				for (int j = 0; j < imgNumPerLine; ++j)
				{
					int x = j * p->frameWidth[state];
					int y = i * p->frameHeight[state];

					//p->AniUnits[state].emplace_back(Rect(x, y, p->frameWidth[state], p->frameHeight[state]));
					p->AniUnits[state][cnt] =  Rect(x, y, p->frameWidth[state], p->frameHeight[state]);
					cnt++;
				}
			}
		}
	}
}
