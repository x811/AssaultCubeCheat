#include "glBegin.h"

void __stdcall Hooks::glBegin::Func(GLenum mode)
{
	return c_hook.GetOriginal<t_glBegin>()(mode);
}

void Hooks::glBegin::Init()
{
	t_glBegin o_glBegin = reinterpret_cast<t_glBegin>(GetProcAddress(GetModuleHandle("opengl32.dll"), "glBegin"));
	c_hook.Create(o_glBegin, Func);
}