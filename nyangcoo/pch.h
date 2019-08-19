﻿// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include <tinyxml2.h>
#include <gdiplus.h>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "CriticalSec.h"

#include "common.h"

#include "Object.h"
#include "StaticObject.h"
#include "Scene.h"

#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "CharacterGraphicsComponent.h"
#include "EffectGraphicsComponent.h"

#include "Character.h"

#include "Effect.h"
#include "Btn.h"
#include "PopUp.h"
#include "MakeCharacterBtn.h"
#include "UpgradeCharacterBtn.h"
#include "PlayerSkillBtn.h"

#include "GameScene.h"
#include "StartScene.h"
#include "LoadGameScene.h"
#include "ChapterSelectScene.h"
#include "CookieSelectScene.h"
#include "ScriptScene.h"

#include "GameStage.h"


#include "XmlManager.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "GameManager.h"

using namespace tinyxml2;
using namespace Gdiplus;
#pragma comment (lib, "gdiplus.lib")

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define FRAME_DEBUG // 프레임 확인용 디파인 . 출력 필요없으면 주석처리하기.

#endif PCH_H
