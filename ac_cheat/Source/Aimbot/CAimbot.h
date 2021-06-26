#pragma once
#include <Windows.h>
#include <algorithm>
#include "../Utils/CInitialization.h"
#include "../../Source/Misc_Exploits/Misc.h"

class CAimbot
{
public:
	void Run();
	CPlayer* GetClosestToXHair(float& fov);
};

extern CAimbot g_Aimbot;

