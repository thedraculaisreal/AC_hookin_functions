// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <atomic>
#include "constants.h"
#include "../feautures/aimbot.h"
#include "../hook/hook.h"

std::atomic<bool> running(true);

BOOL _stdcall hkwglSwapBuffers(HDC hdc)
{
    reset_pointers();
    aimbot.do_aimbot();

    return owglSwapBuffers(hdc);
}

void console(HMODULE hModule) noexcept
{

    AllocConsole();

    // Redirect the standard input/output streams to the console
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);

    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
    owglSwapBuffers = (twglSwapBuffers)TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);

    while (running)
    {
        std::string input;
        std::cin >> input;

        if (input == "quit")
        {
            std::cout << "Exiting console freed...";
            running = false;
        }
    }

    fclose(f);

    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);
}

void hook(HMODULE hModule) noexcept
{


    //while (running)
    //{
    //    reset_pointers();
    //    aimbot.do_aimbot();
    //}

    //FreeLibraryAndExitThread(hModule, 0);
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

        if (thread)
            CloseHandle(thread);
    }

    return TRUE;
}

