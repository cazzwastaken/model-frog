#include "memory.h"

#include <Windows.h>
#include <vector>
#include <stdexcept>

void m::Init()
{
    if (!(sigs.clCheckPureServerWhiteList = Scan("engine", "8B 0D ? ? ? ? 56 83 B9 ? ? ? ? ? 7E 6E ")))
        throw std::runtime_error("Outdated pattern for clCheckPureServerWhiteList");
}

uint8_t* m::Scan(const char* module, const char* pattern) noexcept
{
    const auto handle = ::GetModuleHandle(module);

    if (!handle)
        return nullptr;

    static auto patternToByte = [](const char* pattern)
    {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?') {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
            {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };


    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = patternToByte(pattern);
    auto scanBytes = reinterpret_cast<uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    return nullptr;
}
