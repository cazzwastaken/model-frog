#pragma once
#include <string_view>

#include "../sdk/sdk.h"

// Namespace used to capture and access global interface pointers
namespace i
{
	void Init();

	template <typename T>
	T* Get(const char* module, const std::string_view version) noexcept;

	// Pointers
	inline BaseClient* client = nullptr;
	inline EngineClient* engine = nullptr;
	inline FileSystem* fileSystem = nullptr;
	inline MdlCache* mdlCache = nullptr;
}
