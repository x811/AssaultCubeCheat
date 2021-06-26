#include "wndProc.h"

#include "../../../Menu/ImGui/imgui_impl_win32.h"
#include "../../../Menu/ImGui/imgui_impl_opengl2.h"
#include "../../../Menu/ImGui/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LONG __stdcall Hooks::WndProc::Func(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (g_Menu.bOpen)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		{
			return true;
		}

		ImGuiIO& io = ImGui::GetIO();

		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			io.MouseDown[1] = !io.MouseDown[0];
			return 0;
		case WM_RBUTTONDOWN:
			io.MouseDown[1] = !io.MouseDown[1];
			return 0;
		case WM_MBUTTONDOWN:
			io.MouseDown[2] = !io.MouseDown[2];
			return 0;
		case WM_MOUSEWHEEL:
			return 0;
		case WM_MOUSEMOVE:
			io.MousePos.x = (signed short)(lParam);
			io.MousePos.y = (signed short)(lParam >> 16);
			return 0;
		}
	}

	return CallWindowProc(Original, hWnd, uMsg, wParam, lParam);
}

void Hooks::WndProc::Init()
{
	hwWindow = FindWindow(NULL, "AssaultCube");
	Original = (WNDPROC)SetWindowLongPtr(hwWindow, GWL_WNDPROC, (LONG_PTR)Func);
}