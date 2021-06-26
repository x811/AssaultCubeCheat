#pragma once
#include <Windows.h>
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_opengl2.h"
#include "../ImGui/imgui.h"

namespace vars
{
	extern bool m_bAimBot;
	extern float m_fFov;
	extern bool m_bVisible;
	extern bool m_bTeamAim;

	extern bool m_bPseudoWalls;

	extern bool m_bOnlyHeadShot;
	extern bool m_bTeleKill;
	extern bool m_bNoRecoil;
	extern bool m_bTrigger;
}

class CMenu
{
public:
	bool bOpen;

	void Initialize();
	void Update();
	void ShutDown();
};

extern CMenu g_Menu;