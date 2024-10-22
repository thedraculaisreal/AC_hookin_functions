#include "constants.h"

extern HMODULE hModule = GetModuleHandle(L"ac_client.exe");
extern uintptr_t exeBaseAddress = (uintptr_t)(GetModuleHandle(L"ac_client.exe"));
extern Entity* localPlayer = *(Entity**)(exeBaseAddress + 0x17E0A8);
extern DWORD* entityList = (DWORD*)(exeBaseAddress + 0x18AC04);
extern int numPlayers = (*(int*)(exeBaseAddress + 0x191FD4));

void reset_pointers()
{
    do {

        exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);
        localPlayer = *(Entity**)(exeBaseAddress + 0x17E0A8);
        entityList = (DWORD*)(exeBaseAddress + 0x18AC04);
        numPlayers = (*(int*)(exeBaseAddress + 0x191FD4));

    } while (!exeBaseAddress && !localPlayer && !entityList && !numPlayers);
}
