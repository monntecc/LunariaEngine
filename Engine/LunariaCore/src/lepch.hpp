#pragma once

#include "LunariaCore/Global/PlatformDetection.hpp"

#ifdef LU_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "LunariaCore/Global/Base.hpp"
#include "LunariaCore/Global/Log.hpp"

#ifdef LU_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // LU_PLATFORM_WINDOWS