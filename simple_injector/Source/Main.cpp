#include <Windows.h>
#include <windowsx.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <libloaderapi.h>

void get_proc_id(const char* szProcName, DWORD& procId)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);

		if (Process32First(hSnap, &pEntry))
		{
			do
			{
				if (!strcmp(szProcName, pEntry.szExeFile))
				{
					procId = pEntry.th32ProcessID;
					break;
				}
			}
			while (Process32Next(hSnap, &pEntry));
		}
	}
	CloseHandle(hSnap);
}

void show_error_msg(const char* error_msg)
{
	MessageBox(0, error_msg, "Error", MB_OK);
	exit(-1);
}

bool file_exists(std::string file_name)
{
	struct stat buffer;
	return (stat(file_name.c_str(), &buffer) == 0);
}

int main()
{
	DWORD procId = NULL;
	char dll_path[MAX_PATH];

	const char* file_name = "ac_cheat.dll";
	const char* target_name = "ac_client.exe";

	if (!file_exists(file_name))
	{
		show_error_msg("File Doesnt Exist");
	}

	if (!GetFullPathName(file_name, MAX_PATH, dll_path, nullptr))
	{
		show_error_msg("Failed To Get Full Path");
	}

	get_proc_id(target_name, procId);
	if(procId == NULL)
	{
		show_error_msg("Failed To Get Process Id");
	}
	
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	if (hProc == NULL)
	{
		show_error_msg("Handle Not Defined");
	}

	void* allocated_memory = VirtualAllocEx(hProc, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!allocated_memory)
	{
		show_error_msg("Memory Not Allocated");
	}

	if (!WriteProcessMemory(hProc, allocated_memory, dll_path, MAX_PATH, nullptr))
	{
		show_error_msg("Failed To WriteProcessMemory");
	}

	HANDLE hRemote = CreateRemoteThread(hProc, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
	if (!hRemote)
	{
		show_error_msg("Remote Thread Failed");
	}

	CloseHandle(hProc);
	VirtualFreeEx(hProc, allocated_memory, NULL, MEM_RELEASE);
	MessageBox(0, "Injected", "Success", MB_OK);
}