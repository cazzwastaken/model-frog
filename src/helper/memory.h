#pragma once
#include <cstdint>
#include <cstddef>

// Namespace holding memory related functions
namespace m
{
	void Init();

	// Return pointer to virtual function
	constexpr void* Get(void* thisptr, const size_t index) noexcept
	{
		return (*static_cast<void***>(thisptr))[index];
	}

	// Wrapper to call virtual functions
	template <typename T, typename ... U>
	constexpr T Call(void* thisptr, const size_t index, U ... params) noexcept
	{
		using Fn = T(__thiscall*)(void*, decltype(params)...);
		return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
	}

	// Convert and address from relative to absolute
	template <typename T = uintptr_t>
	constexpr T RelativeToAbsolute(const uintptr_t address) noexcept
	{
		return static_cast<T>(address + 4 + *reinterpret_cast<uint32_t*>(address));
	}

	// Put sigs here fam
	inline struct Signatures
	{
		uint8_t* clCheckPureServerWhiteList = nullptr;
	}sigs;

	// Signature scanner :)
	uint8_t* Scan(const char* module, const char* pattern) noexcept;
}
