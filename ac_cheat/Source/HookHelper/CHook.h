#pragma once
#include <Windows.h>
#include "../../MinHook/MinHook.h"

class CHook
{
	void* m_pOriginal;

public:
	void Create(void* pFromFunc, void* toReplaceWith)
	{
		if (MH_CreateHook(pFromFunc, toReplaceWith, &m_pOriginal) != MH_STATUS::MH_OK)
			return;
	}

	template <typename T>
	inline T GetOriginal()
	{
		return reinterpret_cast<T>(m_pOriginal);
	}
};