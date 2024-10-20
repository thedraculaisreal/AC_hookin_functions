#pragma once
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "../entities/entity.h"
#include "../feautures/gltext.h"
#include "../feautures/gldraw.h"


extern HMODULE hModule;
extern uintptr_t exe_base_address;
extern Entity* local_player;
extern DWORD* entity_list;
extern int num_players;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hdc);
inline twglSwapBuffers wglSwapBuffersGateway;

extern GL::Font glFont;
extern const int FONT_HEIGHT = 15;
extern const int FONT_WIDTH = 9;

extern const char* example = "ESP Box";
extern const char* example2 = "I'm inside";

void draw();

void reset_pointers();
