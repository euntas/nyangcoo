#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Exit,
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
	eObjectType_Cnt
};

class InputComponent;
class Object;
class GraphicsComponent;