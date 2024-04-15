#pragma once

#include <memory>

#include "LunariaCore/Global/PlatformDetection.hpp"

#ifndef LU_DEBUG
	#define LU_ENABLE_ASSERTS 1
#endif // LU_DEBUG

#define LU_EXPAND_MACRO(x) x
#define LU_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define LU_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Lunaria {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
}

#include "LunariaCore/Global/Log.hpp"
#include "LunariaCore/Global/Assert.hpp"