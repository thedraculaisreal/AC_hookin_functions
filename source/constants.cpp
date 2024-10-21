#include "constants.h"

extern HMODULE hModule = GetModuleHandle(L"ac_client.exe");
extern uintptr_t exe_base_address = (uintptr_t)(GetModuleHandle(L"ac_client.exe"));
extern Entity* local_player = *(Entity**)(exe_base_address + 0x17E0A8);
extern DWORD* entity_list = (DWORD*)(exe_base_address + 0x18AC04);
extern int num_players = (*(int*)(exe_base_address + 0x191FD4)); 

void reset_pointers()
{
    do {

        exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
        local_player = *(Entity**)(exe_base_address + 0x17E0A8);
        entity_list = (DWORD*)(exe_base_address + 0x18AC04);
        num_players = (*(int*)(exe_base_address + 0x191FD4));

    } while (!exe_base_address && !local_player && !entity_list && !num_players);
}
