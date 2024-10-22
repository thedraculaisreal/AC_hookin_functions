#pragma once
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "../entities/entity.h"


extern HMODULE hModule;
extern uintptr_t exeBaseAddress;
extern Entity* localPlayer;
extern DWORD* entityList;
extern int numPlayers;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hdc);
inline twglSwapBuffers wglSwapBuffersGateway;

void reset_pointers();
