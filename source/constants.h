#pragma once
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "../entities/entity.h"
#include "../opengl/gldraw.h"


extern HMODULE hModule;
extern uintptr_t exe_base_address;
extern Entity* local_player;
extern DWORD* entity_list;
extern int num_players;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hdc);
inline twglSwapBuffers wglSwapBuffersGateway;

extern GL::Font glFont;

extern const int FONT_HEIGHT;
extern const int FONT_WIDTH;

extern const char* example;
extern const char* example2;

void draw();

void reset_pointers();
