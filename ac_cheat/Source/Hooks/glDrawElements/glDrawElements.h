#pragma once
#include "../../Utils/CInitialization.h"
#include "../../HookHelper/CHook.h"

#pragma comment(lib, "OpenGL32.lib")
#include <gl/GL.h>

namespace Hooks
{
	namespace glDrawElements
	{
		inline CHook c_hook;
		typedef void(__stdcall* t_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indice);
		void __stdcall Func(GLenum mode, GLsizei count, GLenum type, const void* indice);
		void Init();
	}
}