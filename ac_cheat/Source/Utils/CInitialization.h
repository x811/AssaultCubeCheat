#pragma once
#include <Windows.h>
#include "Utils.h"
#include "SDK.h"

namespace offsets
{
	extern uintptr_t ent_list;
	extern uintptr_t local_player;
	extern uintptr_t num_of_players;
};

namespace GData
{
	extern uintptr_t module_start;
	extern CPlayer* aimPlayer;

	extern EntityList* p_list;
	extern CPlayer* p_local;
	extern int p_num;
}

class CInitialization
{
public:
	void UpdateData();
};

extern CInitialization g_Manager;

