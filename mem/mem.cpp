#include "mem.h"

bool Mem::Detour32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5)
		return false;

	// Old protection before we overwrite it
	DWORD curProtection;

	// Gives permission to write to the executing memory, which is disabled by default by windows
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	// Calculation for new address
	uintptr_t relativeAddress = dst - src - 5;

	// Creates jmpcode at hookedspot
	*src = 0xE9;

	// Address for hooking
	*(uintptr_t*)(src + 1) = relativeAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}
BYTE* Mem::TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5)
		return 0;
	// Create Gateway
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Write stolen bytes to the gateway
	memcpy_s(gateway, len, src, len);

	// Get the gateway to destinatioon address
	uintptr_t gatewayRelativeAddr = src - gateway - 5;

	// Add the jump opcode at the end
	*(gateway + len) = 0xE9;

	// Write the address of the gateway to the jmp
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

	// Perform the detour
	Detour32(src, dst, len);

	return gateway;

}