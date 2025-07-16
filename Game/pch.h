#pragma once

// Windows
#include <Windows.h>
#include <assert.h>
#include <cstdlib>

// CRT Debug
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// 사운드 & AlphaBlend
#include <MMSystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "msimg32.lib")

// STL
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

// 엔진 전역 정의
#include "Values.h"
#include "Types.h"
#include "Enums.h"
#include "Defines.h"
#include "Utils.h"

// 싱글톤 매니저
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameManager.h"

// 게임 시스템
#include "QuestSystem.h"