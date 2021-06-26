#include "Utils.h"
#include <algorithm>
#include <math.h>
#include "CInitialization.h"

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
		if ((pPlayer->vTable == 0x4E4A98 || pPlayer->vTable == 0x4E4AC0) && pPlayer->m_iHealth > 0)
		{
			return true;
		}
	}

	return false;
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