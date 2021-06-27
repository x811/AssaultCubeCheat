#pragma once
#include <Windows.h>
#include "Utils.h"
#include "SDK.h"

struct glMatrix
{
	float matrix[16];
};

namespace offsets
{
	extern uintptr_t ent_list;
	extern uintptr_t local_player;
	extern uintptr_t num_of_players;
	extern uintptr_t m_iGameMode;
	extern uintptr_t m_ViewMatrix;
};

namespace GData
{
	extern uintptr_t module_start;
	extern CPlayer* aimPlayer;

	extern EntityList* p_list;
	extern CPlayer* p_local;
	extern int g_gamemode;
	extern glMatrix* mvpmatrix;
	extern int p_num;
}

class CInitialization
{
public:
	void UpdateData();
};

extern CInitialization g_Manager;

