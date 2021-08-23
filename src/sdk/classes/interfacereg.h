#pragma once

using InstantiateInterfaceFn = void* (__cdecl*)();

class InterfaceReg
{
public:
	InstantiateInterfaceFn CreateInterface;
	const char* name;
	InterfaceReg* next;
};
