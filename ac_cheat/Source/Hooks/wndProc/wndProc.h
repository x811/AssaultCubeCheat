#pragma once
#include "../../Utils/CInitialization.h"
#include "../../HookHelper/CHook.h"
#include "../../../Menu/src/Menu.h"

namespace Hooks
{
	namespace WndProc
	{
		inline HWND hwWindow;
		inline WNDPROC Original;
		LONG __stdcall Func(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void Init();
	}
}