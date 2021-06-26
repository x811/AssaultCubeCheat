#include "CAimbot.h"
#include "../../Menu/src/Menu.h"

void CAimbot::Run()
{
	if (!vars::m_bAimBot) return;
	if (!GData::p_list) return;
	if (!g_Utils.IsValid(GData::p_local)) return;

	float fov = NULL;
	CPlayer* enemy = GetClosestToXHair(fov);

	if (!enemy) return;
	if (!fov) return;

	Vector3 myHeadPos = GData::p_local->m_vecHeadPos;
	Vector3 eHeadPos = enemy->m_vecHeadPos;

	Vector3 angsToAim;
	g_Utils.CalcAngle(myHeadPos, eHeadPos, angsToAim);

	if (fov < vars::m_fFov)
		GData::p_local->m_vecViewAngles = angsToAim;
}

CPlayer* CAimbot::GetClosestToXHair(float& fov)
{
	float best_delta = FLT_MAX;
	float curr_dist = FLT_MAX;
	CPlayer* bestTarget = nullptr;

	for (int i = 0; i < GData::p_num; i++)
	{
		CPlayer* currPlayer = *(CPlayer**)(*(uintptr_t*)(GData::module_start + offsets::ent_list) + i * 0x4);
		if (!g_Utils.IsValid(currPlayer))
			continue;

		if (currPlayer->m_iTeamNum == GData::p_local->m_iTeamNum && !vars::m_bTeamAim)
			continue;

		if (!g_Utils.IsVisible(currPlayer) && vars::m_bVisible)
			continue;

		Vector3 myHeadPos = GData::p_local->m_vecHeadPos;
		Vector3 eHeadPos = currPlayer->m_vecHeadPos;

		Vector3 angsToAim;
		g_Utils.CalcAngle(myHeadPos, eHeadPos, angsToAim);

		curr_dist = sqrtf(powf((GData::p_local->m_vecViewAngles.x - angsToAim.x), 2) + powf((GData::p_local->m_vecViewAngles.y - angsToAim.y), 2));
		if (curr_dist < best_delta)
		{
			best_delta = curr_dist;
			bestTarget = currPlayer;
			fov = curr_dist;
		}
	}

	return bestTarget;
}

CAimbot g_Aimbot;