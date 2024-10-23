#pragma once
#include <Windows.h>
#include <vector>


bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
void patch(BYTE* dst, BYTE* src, unsigned int size);


struct Hook
{
	bool bStatus{ false };
	BYTE* src{ nullptr };
	BYTE* dst{ nullptr };
	BYTE* PtrToGatewayFnPtr{ nullptr };
	uintptr_t len{ 0 };

	BYTE originalBytes[10]{ 0 };

	Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);

	void enable();
	void disable();
	void toggle();
};
