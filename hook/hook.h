#pragma once
#include <Windows.h>
#include <vector>

namespace Hook
{
	bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
	BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
}

