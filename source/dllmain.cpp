// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <atomic>
#include "constants.h"
#include "../feautures/aimbot.h"
#include "../hook/hook.h"
#include "../opengl/gldraw.h"

std::atomic<bool> running(true);

BOOL _stdcall hkwglSwapBuffers(HDC hdc)
{
    GL::font.draw();
    return wglSwapBuffersGateway(hdc);
}

void console(HMODULE hModule) noexcept
{

    AllocConsole();

    // Redirect the standard input/output streams to the console
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);

    Hook SwapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);

    SwapBuffersHook.enable();

    while (running)
    {
        std::string input;
        std::cin >> input;

        if (input == "quit")
        {
            std::cout << "Exiting...\n";
            std::cout << "Console freed.";
            running = false;
        }
    }

    SwapBuffersHook.disable();

    if (f != 0)
        fclose(f);

    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);
}

void aimbotHook(HMODULE hModule) noexcept
{


    while (running)
    {
        reset_pointers();
        aimbot.doAimbot();
        Sleep(1);
    }

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (1 == ul_reason_for_call)
    {
        DisableThreadLibraryCalls(hModule);

        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(console), hModule, 0, nullptr);
        const auto thread1 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(aimbotHook), hModule, 0, nullptr);

        if (thread)
            CloseHandle(thread);
        if (thread1)
            CloseHandle(thread1);
    }

    return TRUE;
}

