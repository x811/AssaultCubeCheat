#pragma once
#include "../../Utils/CInitialization.h"
#include "../../HookHelper/CHook.h"
#include "../../Aimbot/CAimbot.h"
#include "../../Misc_Exploits/Misc.h"

namespace Hooks
{
	namespace wglSwapBuffers
	{
		inline CHook c_hook;
		typedef BOOL(__stdcall* t_wglSwapBuffers)(HDC hdc);
		BOOL __stdcall Func(HDC hdc);
		void Init();
	}
}