#include "wglSwapBuffers.h"
#include "../../../Menu/src/Menu.h"

#pragma comment(lib, "OpenGL32.lib")
#include <gl/GL.h>

BOOL __stdcall Hooks::wglSwapBuffers::Func(HDC hdc)
{
	g_Manager.UpdateData();

	g_Aimbot.Run();

	g_Esp.Run();

	g_Misc.SetHeadshot();
	g_Misc.SetNoRecoil();
	g_Misc.SetTeleKill();
	g_Misc.TriggerBot();

	if (GetAsyncKeyState(VK_INSERT) & 1) //Checks if we want to open menu
	{
		g_Menu.bOpen = !g_Menu.bOpen;
	}

	g_Menu.Update();

	return c_hook.GetOriginal<t_wglSwapBuffers>()(hdc);
}

void Hooks::wglSwapBuffers::Init()
{
	t_wglSwapBuffers o_wglSwapBuffers = reinterpret_cast<t_wglSwapBuffers>(GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers"));
	c_hook.Create(o_wglSwapBuffers, Func);
}