#pragma once
#include "interfaces.h"

namespace h
{
	void Init();
	void Shutdown() noexcept;

	using FindMdlFn = unsigned long(__thiscall*)(void*, const char*);
	inline FindMdlFn FindMdlOriginal = nullptr;
	unsigned long __stdcall FindMdl(const char* path) noexcept;

	using LooseFilesAllowedFn = bool(__thiscall*)(void*);
	inline LooseFilesAllowedFn LooseFilesAllowedOriginal = nullptr;
	bool __stdcall LooseFilesAllowed() noexcept;

	using CL_CheckForPureServerWhitelistFn = void(__thiscall*)(void*);
	inline CL_CheckForPureServerWhitelistFn CL_CheckForPureServerWhitelistOriginal = nullptr;
	void __fastcall CL_CheckForPureServerWhitelist(void* edx, void* ecx) noexcept;
}
