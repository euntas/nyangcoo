#include "pch.h"
#include "PopUp.h"

PopUp::PopUp() : StaticObject(EObjectType::eObjectType_PopUp)
{
	this->x = 300;
	this->y = 300;

	name = ePopup_close;

	bg = new StaticObject();
	bg->Objtype = eObjectType_PopUp;
	bg->AssetFileName = TEXT("sm_good.png");
	bg->rc = Rect(0, 0, 250, 155);

	infoStaticObj.emplace_back(bg);

	
}

void PopUp::Init()
{

}

void PopUp::Update(float Delta)
{
	StaticObject::Update(Delta);
}

void PopUp::Render(Gdiplus::Graphics* pGraphics)
{
	StaticObject::Render(pGraphics);
}

void PopUp::Release()
{

}
