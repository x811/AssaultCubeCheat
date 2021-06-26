#include "CInitialization.h"

namespace offsets
{
	uintptr_t ent_list = 0x10F4F8;
	uintptr_t local_player = 0x10F4F4;
	uintptr_t num_of_players = 0x10F500;
};

namespace GData
{
	uintptr_t module_start;
	CPlayer* aimPlayer;

	EntityList* p_list;
	CPlayer* p_local;
	int p_num;
}

void CInitialization::UpdateData()
{
	GData::p_list = *reinterpret_cast<EntityList**>(GData::module_start + offsets::ent_list);
	GData::p_local = *reinterpret_cast<CPlayer**>(GData::module_start + offsets::local_player);
	GData::p_num = *reinterpret_cast<int*>(GData::module_start + offsets::num_of_players);
}

CInitialization g_Manager;