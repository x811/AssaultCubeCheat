#pragma once
#include "../../Utils/CInitialization.h"
#include "../../HookHelper/CHook.h"

#pragma comment(lib, "OpenGL32.lib")
#include <gl/GL.h>

namespace Hooks
{
	namespace glBegin
	{
		inline CHook c_hook;
		typedef void(__stdcall* t_glBegin)(GLenum mode);
		void __stdcall Func(GLenum mode);
		void Init();
	}
}