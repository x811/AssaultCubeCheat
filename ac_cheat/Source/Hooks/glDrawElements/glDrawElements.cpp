#include "glDrawElements.h"
#include "../../../Menu/src/Menu.h"

void __stdcall Hooks::glDrawElements::Func(GLenum mode, GLsizei count, GLenum type, const void* indice)
{
	if (vars::m_bPseudoWalls)
	{
		glDepthFunc(GL_ALWAYS);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_ALPHA_TEST);
	}

	return c_hook.GetOriginal<t_glDrawElements>()(mode, count, type, indice);
}

void Hooks::glDrawElements::Init()
{
	t_glDrawElements o_glDrawElements = reinterpret_cast<t_glDrawElements>(GetProcAddress(GetModuleHandle("opengl32.dll"), "glDrawElements"));
	c_hook.Create(o_glDrawElements, Func);
}