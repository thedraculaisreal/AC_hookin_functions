#pragma once
#include <Windows.h>
#include <vector>

namespace Mem
{
	bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
	BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
}
