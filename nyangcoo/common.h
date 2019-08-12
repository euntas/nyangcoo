#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Exit,
	eScene_Continue,
	eScene_LoadGame,
	eScene_Challenge,
	eScene_DeleteGame,
	eScene_ChapterSelect,
	eScene_CookieSelect,
	eScene_Cnt
};

enum EObjectType
{
	eObjectType_None,
	eObjectType_Btn,
	eObjectType_Static,
	eObjectType_Player,
	eObjectType_Bullet,
	eObjectType_Enemy,
	eObjectType_BGImage,
	eObjectType_Effect,
	eObjectType_PopUp,
	eObjectType_Cnt
};

enum EState {
	eState_Run,
	eState_Hit,
	eState_Damage,
	eState_Dead,
	eState_Cnt
};

enum EEffect {
	eEffect_fox_Hit,
	eEffect_Cnt
};

enum EPopup {
	ePopup_close,
	ePopup_Cnt
};

class InputComponent;
class Object;
class GraphicsComponent;