#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Exit,
	eScene_Continue,
	eScene_LoadGame,
	eScene_SaveGame,
	eScene_Challenge,
	eScene_DeleteGame,
	eScene_ChapterSelect,
	eScene_CookieSelect,
	eScene_Script,
	eScene_Help,
	eSaveLoadBtn_Select0,
	eSaveLoadBtn_Select1,
	eSaveLoadBtn_Select2,
	eSaveLoadBtn_Load,
	eSaveLoadBtn_Save,
	eScene_Cnt
};

enum EObjectType
{
	eObjectType_None,
	eObjectType_Btn,
	eObjectType_Static,
	eObjectType_Player,
	eObjectType_Character,
	eObjectType_Bullet,
	eObjectType_Enemy,
	eObjectType_BGImage,
	eObjectType_Effect,
	eObjectType_PopUp,
	eObjectType_MakeCharacterBtn,
	eObjectType_UpgradeCharacterBtn,
	eObjectType_PlayerSkillBtn,
	eObjectType_Cnt
};

enum ESkillType
{
	eSkill_Heal,
	eSkill_Blizzard,
	eSkill_Razer,
	eSkill_Cnt
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
	ePopup_result,
	ePopup_saveloadpopup,
	ePopup_save,
	ePopup_load,
	ePopup_Cnt
};

enum ECharacter {
	eCharacter_moonlight,
	eCharacter_pistachio,
	eCharacter_whitechoco,
	eCharacter_muscle,
	eCharacter_windarcher,
	eCharacter_kiwi,
	eCharacter_Cnt
};

class GameStage;
class InputComponent;
class Object;
class Character;
class Effect;
class GraphicsComponent;

#define MAX_WAVE_NUM 4
#define ALL_STAGE_NUM 4