#pragma once

#include "LunariaCore/Global/Base.hpp"
#include "LunariaCore/Global/Log.hpp"

#include <filesystem>

#ifdef LU_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define LU_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LU##type##ERROR(msg, __VA_ARGS__); } }
	#define LU_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LU_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define LU_INTERNAL_ASSERT_NO_MSG(type, check) LU_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LU_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define LU_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LU_INTERNAL_ASSERT_GET_MACRO(...) LU_EXPAND_MACRO( LU_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LU_INTERNAL_ASSERT_WITH_MSG, LU_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define LU_ASSERT(...) LU_EXPAND_MACRO( LU_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define LU_CORE_ASSERT(...) LU_EXPAND_MACRO( LU_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define LU_ASSERT(...)
	#define LU_CORE_ASSERT(...)
#endif