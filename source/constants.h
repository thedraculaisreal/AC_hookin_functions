#pragma once
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "../entities/entity.h"


extern HMODULE hModule;
extern uintptr_t exe_base_address;
extern Entity* local_player;
extern DWORD* entity_list;
extern int num_players;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hdc);
inline twglSwapBuffers owglSwapBuffers;

void reset_pointers();
