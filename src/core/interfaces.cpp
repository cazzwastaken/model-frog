#include "interfaces.h"

#include <Windows.h>
#include <stdexcept>

void i::Init()
{
	if (!(client = Get<BaseClient>("client", "VClient")))
		throw std::runtime_error("Failed to get client interface.");

	if (!(engine = Get<EngineClient>("engine", "VEngineClient")))
		throw std::runtime_error("Failed to get engine interface.");

	if (!(fileSystem = Get<FileSystem>("filesystem_stdio", "VFileSystem")))
		throw std::runtime_error("Failed to get fileSystem interface.");

	if (!(mdlCache = Get<MdlCache>("datacache", "MDLCache")))
		throw std::runtime_error("Failed to get mdlCache interface.");
}

template <typename T>
T* i::Get(const char* module, const std::string_view version) noexcept
{
	const auto handle = GetModuleHandle(module);

	if (!handle)
		return nullptr;

	const auto createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));

	if (!createInterface)
		return nullptr;

	const auto relative = createInterface + 5;
	const auto address = m::RelativeToAbsolute(relative);
	const auto interfaces = **reinterpret_cast<InterfaceReg***>(address + 6);

	if (!interfaces)
		return nullptr;

	for (auto item = interfaces; item; item = item->next)
	{
		if ((!std::string_view(item->name).compare(0U, version.length(), version) &&
			std::atoi(item->name + version.length()) > 0) ||
			!version.compare(item->name))
		{
			const auto pointer = item->CreateInterface();

			if (!pointer)
				return nullptr;

			return static_cast<T*>(pointer);
		}
	}

	return nullptr;
}
