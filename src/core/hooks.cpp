#include "hooks.h"

#include "../../external/minhook/minhook.h"
#include <stdexcept>

void h::Init()
{
	if (MH_Initialize())
		throw std::runtime_error("Unable to initialize minhook");

	if (MH_CreateHook(m::Get(i::client, 37), &FrameStageNotify, reinterpret_cast<void**>(&FrameStageNotifyOriginal)))
		throw std::runtime_error("Unable to hook FrameStageNotify().");

	if (MH_CreateHook(m::Get(i::mdlCache, 10), &FindMdl, reinterpret_cast<void**>(&FindMdlOriginal)))
		throw std::runtime_error("Unable to hook FindMdl().");

	if (MH_CreateHook(m::Get(i::fileSystem, 128), &LooseFilesAllowed, reinterpret_cast<void**>(&LooseFilesAllowedOriginal)))
		throw std::runtime_error("Unable to hook LooseFilesAllowed().");

	if (MH_CreateHook(m::sigs.clCheckPureServerWhiteList,
		&CL_CheckForPureServerWhitelist,
		reinterpret_cast<void**>(&CL_CheckForPureServerWhitelistOriginal)))
		throw std::runtime_error("Unable to hook CL_CheckForPureServerWhitelist().");

	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Unable to enable hooks");
}

void h::Shutdown() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

void __stdcall h::FrameStageNotify(ClientFrameStage stage) noexcept
{
	// Empty for now
	if (stage == ClientFrameStage::FRAME_RENDER_START)
	{

	}

	return FrameStageNotifyOriginal(i::client, stage);
}

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/214760-hooking-findmdl.html
unsigned long __stdcall h::FindMdl(const char* path) noexcept
{
	// Do sneaky model stuff here

	if (strstr(path, "knife_default_ct.mdl"))
		return FindMdlOriginal(i::mdlCache, "models/weapons/v_minecraft_pickaxe.mdl");
	else if (strstr(path, "knife_default_t.mdl"))
		return FindMdlOriginal(i::mdlCache, "models/weapons/v_knife_dildo_test.mdl");

	return FindMdlOriginal(i::mdlCache, path);
}

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/394153-fixing-chams-sv_pure_allow_loose_file_loads.html
bool __stdcall h::LooseFilesAllowed() noexcept
{
	// Allow the files :think:
	return true;
}

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/engine/cl_main.cpp#L1510
void __fastcall h::CL_CheckForPureServerWhitelist(void* edx, void* ecx) noexcept
{
	// Stop the game from checking the whitelist lmao
	return;
}
