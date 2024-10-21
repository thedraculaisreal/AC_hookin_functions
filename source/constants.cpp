#include "constants.h"

extern HMODULE hModule = GetModuleHandle(L"ac_client.exe");
extern uintptr_t exe_base_address = (uintptr_t)(GetModuleHandle(L"ac_client.exe"));
extern Entity* local_player = *(Entity**)(exe_base_address + 0x17E0A8);
extern DWORD* entity_list = (DWORD*)(exe_base_address + 0x18AC04);
extern int num_players = (*(int*)(exe_base_address + 0x191FD4)); 

extern const int FONT_HEIGHT = 15;
extern const int FONT_WIDTH = 9;

extern const char* example = "ESP Box";
extern const char* example2 = "I'm inside";

extern GL::Font glFont{ NULL };

void reset_pointers()
{
    do {

        exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
        local_player = *(Entity**)(exe_base_address + 0x17E0A8);
        entity_list = (DWORD*)(exe_base_address + 0x18AC04);
        num_players = (*(int*)(exe_base_address + 0x191FD4));

    } while (!exe_base_address && !local_player && !entity_list && !num_players);
}

void draw()
{
    HDC currentHDC = wglGetCurrentDC();

    if (!glFont.bBuilt || currentHDC != glFont.hdc)
    {
        glFont.build(FONT_HEIGHT);
    }

    GL::setupOrtho();

    GL::drawOutline(300, 300, 200, 200, 2.0f, rgb::red);

    float textPointX = glFont.centerText(300, 200, strlen(example) * FONT_WIDTH);
    float textPointY = 300 - FONT_HEIGHT / 2;

    glFont.print(textPointX, textPointY, rgb::green, "%s", example);

    vec3 insideTextPoint = glFont.centerText(300, 300 + 100, 200, 200, strlen(example2) * FONT_WIDTH, FONT_HEIGHT);
    glFont.print(insideTextPoint.x, insideTextPoint.y, rgb::green, "%s", example2);

    GL::restoreGl();
}