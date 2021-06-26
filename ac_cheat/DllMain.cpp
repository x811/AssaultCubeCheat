#include <Windows.h>
#include <windowsx.h>
#include <thread>

#include "Source/Hooks/wndProc/wndProc.h"
#include "Source/Hooks/SwapBuffers/wglSwapBuffers.h"
#include "Source/Hooks/glDrawElements/glDrawElements.h"
#include "Source/Hooks/glBegin/glBegin.h"

#include "Menu/src/Menu.h"

BOOL WINAPI AC_INIT(HMODULE hMod)
{
	GData::module_start = (uintptr_t)GetModuleHandle("ac_client.exe");

	g_Menu.Initialize();

	MH_Initialize();
	{
		Hooks::WndProc::Init();
		Hooks::wglSwapBuffers::Init();
		Hooks::glDrawElements::Init();
		Hooks::glBegin::Init();
		//Hooks::Attack::Init();
	}
	MH_EnableHook(MH_ALL_HOOKS);

	while (!(GetAsyncKeyState(VK_DELETE) & 1))
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	g_Menu.ShutDown();
	MH_Uninitialize();
	MessageBox(0, "Uninjected", "OK", MB_OK);
	FreeLibraryAndExitThread(hMod, NULL);
	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hInstnace, DWORD reason, LPVOID lpr)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)AC_INIT, hInstnace, NULL, nullptr));
	}

	return TRUE;
}