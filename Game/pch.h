#pragma once

#include "Values.h"
#include "Types.h"
#include "Enums.h"
#include "Defines.h"
#include "Utils.h"

#include <Windows.h>
#include <functional>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

#include <assert.h>

// C++20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// AlphaBlend
#pragma comment(lib, "msimg32.lib")

// »ç¿îµå
#include <MMSystem.h>
#include <dsound.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dsound.lib")