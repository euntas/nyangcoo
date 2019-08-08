#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Exit,
	eScene_Continue,
	eScene_Load,
	eScene_Challenge,
	eScene_DeleteGame
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
	eObjectType_Cnt
};

enum EState {
	eState_Run,
	eState_Hit,
	eState_Damage,
	eState_Dead,
	eState_Cnt
};

class InputComponent;
class Object;
class GraphicsComponent;