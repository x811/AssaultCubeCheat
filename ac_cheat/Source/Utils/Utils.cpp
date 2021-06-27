#include "Utils.h"
#include <algorithm>
#include <math.h>
#include "CInitialization.h"
#include "../ESP/Drawing.h"

#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

uintptr_t Utils::FindSignature(const char* szModule, const char* szSignature)
{
	const char* pat = szSignature;
	uintptr_t START_RANGE, END_RANGE;
	uintptr_t firstMatch;

	START_RANGE = (uintptr_t)GetModuleHandle(szModule);
	if (!START_RANGE)
		return NULL;

	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)START_RANGE, &modInfo, sizeof(modInfo));

	END_RANGE = START_RANGE + modInfo.SizeOfImage;

	for (uintptr_t i = START_RANGE; i < END_RANGE; i++)
	{
		if (!*pat)
			return firstMatch;

		if (*(BYTE*)pat == '\?' || *(BYTE*)i == GET_BYTE(pat))
		{
			if (!firstMatch)
				firstMatch == i;

			if (!pat[2])
				return firstMatch;

			if (*(BYTE*)pat == '\?\?' || *(BYTE*)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}

		else
		{
			pat = szSignature;
			firstMatch = 0;
		}
	}

	return NULL;
}

float Utils::DistanceVec3(const Vector3& from, const Vector3& to)
{
	float distance;
	distance = sqrtf(powf(to.x - from.x, 2) + powf(to.y - from.y, 2) + powf(to.z - from.z, 2));
	return distance;
}

bool screen_transform(const Vector3& point, Vector3& screen)
{
	Vector2 screen_size = GL::GetRes();

	Vector3 clipCoords;
	clipCoords.x = GData::mvpmatrix->matrix[0] * point.x + GData::mvpmatrix->matrix[4] * point.y + GData::mvpmatrix->matrix[8] * point.z + GData::mvpmatrix->matrix[12];
	clipCoords.y = GData::mvpmatrix->matrix[1] * point.x + GData::mvpmatrix->matrix[5] * point.y + GData::mvpmatrix->matrix[9] * point.z + GData::mvpmatrix->matrix[13];
	clipCoords.z = GData::mvpmatrix->matrix[2] * point.x + GData::mvpmatrix->matrix[6] * point.y + GData::mvpmatrix->matrix[10] * point.z + GData::mvpmatrix->matrix[14];

	float w = GData::mvpmatrix->matrix[3] * point.x + GData::mvpmatrix->matrix[7] * point.y + GData::mvpmatrix->matrix[11] * point.z + GData::mvpmatrix->matrix[15];
	if (w < 0.01f)
		return true;

	screen.x = clipCoords.x / w;
	screen.y = clipCoords.y / w;
	screen.z = 0;
	return false;
}

bool Utils::World2Screen(const Vector3& point, Vector3& screen)
{
	const Vector2 screen_size = GL::GetRes();

	Vector3 temp;
	if (!screen_transform(point, temp))
	{
		screen.x = (screen_size.x / 2 * temp.x) + (temp.x + screen_size.x / 2);
		screen.y = -(screen_size.y / 2 * temp.y) + (temp.y + screen_size.y / 2);
		return true;
	}
	/*Vector2 screen_size = GL::GetRes();

	float w = GData::mvpmatrix->matrix[3] * point.x + GData::mvpmatrix->matrix[7] * point.y + GData::mvpmatrix->matrix[11] * point.z + GData::mvpmatrix->matrix[15];
	if (w < 0.01f)
		return false;

	Vector3 clipCoords;
	clipCoords.x = GData::mvpmatrix->matrix[0] * point.x + GData::mvpmatrix->matrix[4] * point.y + GData::mvpmatrix->matrix[8] * point.z + GData::mvpmatrix->matrix[12];
	clipCoords.y = GData::mvpmatrix->matrix[1] * point.x + GData::mvpmatrix->matrix[5] * point.y + GData::mvpmatrix->matrix[9] * point.z + GData::mvpmatrix->matrix[13];
	clipCoords.z = GData::mvpmatrix->matrix[2] * point.x + GData::mvpmatrix->matrix[6] * point.y + GData::mvpmatrix->matrix[10] * point.z + GData::mvpmatrix->matrix[14];

	Vector3 NDC;
	NDC.x = clipCoords.x / w;
	NDC.y = clipCoords.y / w;
	NDC.z = clipCoords.z / w;

	screen.x = (screen_size.x / 2 * NDC.x) + (NDC.x + screen_size.x / 2);
	screen.y = -(screen_size.y / 2 * NDC.y) + (NDC.y + screen_size.y / 2);*/
	return true;
}

bool Utils::isOnScreen(const Vector3& point, Vector3& screen)
{
	if (!World2Screen(point, screen)) return false;
	Vector2 screen_size = GL::GetRes();
	bool xOk = screen_size.x > screen.x > 0, yOk = screen_size.y > screen.y > 0;
	return xOk && yOk;
}

bool Utils::CalcAngle(const Vector3& from, const Vector3& to, Vector3& result)
{
	Vector3 delta = Vector3(to.x - from.x, to.y - from.y, to.z - from.z);
	float VecLength = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
	result.x = -atan2f(delta.x, delta.y) * 180.f / (float)M_PI + 180.f;
	result.y = asinf(delta.z / VecLength) * 180.f / (float)M_PI;
	result.z = NULL;

	return true;
}

bool Utils::IsValid(CPlayer* pPlayer)
{
	if (pPlayer != nullptr)
	{
		if ((pPlayer->vTable == 0x4E4A98 || pPlayer->vTable == 0x4E4AC0) && pPlayer != GData::p_local && pPlayer->m_iHealth > 0)
		{
			return true;
		}
	}

	return false;
}

bool Utils::IsTeamGameMode()
{
	return (GData::g_gamemode == 0 || GData::g_gamemode == 4 || GData::g_gamemode == 5 || GData::g_gamemode == 7 || GData::g_gamemode == 11 || GData::g_gamemode == 13 || GData::g_gamemode == 14 || GData::g_gamemode == 16 || GData::g_gamemode == 17 || GData::g_gamemode == 20 || GData::g_gamemode == 21);
}

struct trace_result
{
	Vector3 end;
	bool collided;
};

bool Utils::IsVisible(CPlayer* pPlayer)
{
	DWORD func = 0x48A310;
	trace_result trace_t;
	trace_t.collided = false;

	Vector3 from = GData::p_local->m_vecHeadPos;
	Vector3 to = pPlayer->m_vecHeadPos;

	__asm
	{
		push 0
		push 0
		push GData::p_local
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [trace_t]
		call func
		add esp, 36
	}

	return !trace_t.collided;
}

Utils g_Utils;