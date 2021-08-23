#include <Windows.h>
#include <thread>

#include "core/hooks.h"

// Error macro
#define MESSAGE(message) \
MessageBeep(MB_ICONSTOP); \
MessageBoxA(NULL, message, "kakhack", MB_OK | MB_ICONERROR)


void Initialize(HMODULE module)
{
	while (!GetModuleHandle("serverbrowser"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// Initialize cheat
	try
	{
		m::Init();
		i::Init();
	}
	catch (const std::exception& error)
	{
		MESSAGE(error.what());
		FreeLibraryAndExitThread(module, EXIT_SUCCESS);
	}

	try
	{
		h::Init();
	}
	catch (const std::exception& error)
	{
		h::Shutdown();
		MESSAGE(error.what());
		FreeLibraryAndExitThread(module, EXIT_SUCCESS);
	}

	//while (!GetAsyncKeyState(VK_END))
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// Shutdown
	//h::Shutdown();

	//FreeLibraryAndExitThread(module, EXIT_SUCCESS);
}

// Entry point
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		// Create our initialization thread
		const auto thread = CreateThread(nullptr,
			NULL,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize),
			instance,
			NULL,
			nullptr);

		// Cleanup our handle
		if (thread)
			CloseHandle(thread);
	}

	return TRUE;
}
