#include "CInitialization.h"

namespace offsets
{
	uintptr_t ent_list = 0x10F4F8;
	uintptr_t local_player = 0x10F4F4;
	uintptr_t num_of_players = 0x10F500;
	uintptr_t m_iGameMode = 0x10F49C;
	uintptr_t m_ViewMatrix = 0x101AE8;
};

namespace GData
{
	uintptr_t module_start;
	CPlayer* aimPlayer;

	EntityList* p_list;
	CPlayer* p_local;
	int g_gamemode;
	glMatrix* mvpmatrix;
	int p_num;
}

void CInitialization::UpdateData()
{
	GData::p_list = *reinterpret_cast<EntityList**>(GData::module_start + offsets::ent_list);
	GData::p_local = *reinterpret_cast<CPlayer**>(GData::module_start + offsets::local_player);

	GData::g_gamemode = *reinterpret_cast<int*>(GData::module_start + offsets::m_iGameMode);
	GData::mvpmatrix = reinterpret_cast<glMatrix*>(GData::module_start + offsets::m_ViewMatrix);
	GData::p_num = *reinterpret_cast<int*>(GData::module_start + offsets::num_of_players);
}

CInitialization g_Manager;