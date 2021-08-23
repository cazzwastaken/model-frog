#pragma once
#include "interfaces.h"

namespace h
{
	void Init();
	void Shutdown() noexcept;

	using FrameStageNotifyFn = void(__thiscall*)(void*, ClientFrameStage);
	inline FrameStageNotifyFn FrameStageNotifyOriginal = nullptr;
	void __stdcall FrameStageNotify(ClientFrameStage stage);

	using FindMdlFn = unsigned long(__thiscall*)(void*, const char*);
	inline FindMdlFn FindMdlOriginal = nullptr;
	unsigned long __stdcall FindMdl(const char* path);

	using LooseFilesAllowedFn = bool(__thiscall*)(void*);
	inline LooseFilesAllowedFn LooseFilesAllowedOriginal = nullptr;
	bool __stdcall LooseFilesAllowed();

	using SendNetMsgFn = bool(__thiscall*)(void*, NetMessage&, bool, bool);
	inline SendNetMsgFn SendNetMsgOriginal = nullptr;
	bool __stdcall SendNetMsg(NetMessage& message, bool forceReliable, bool voice);
}
