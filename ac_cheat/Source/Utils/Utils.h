#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "SDK.h"

class Utils
{
public:
	static uintptr_t FindSignature(const char* szModule, const char* szSignature);
	bool IsValid(CPlayer* pPlayer);
	bool IsVisible(CPlayer* pPlayer);
	bool IsTeamGameMode();

	bool CalcAngle(const Vector3& from, const Vector3& to, Vector3& result);
	float DistanceVec3(const Vector3& from, const Vector3& to);
	bool World2Screen(const Vector3& point, Vector3& screen);
	bool isOnScreen(const Vector3& point, Vector3& screen);
};

extern Utils g_Utils;

