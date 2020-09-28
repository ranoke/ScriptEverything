#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>

//first option - Injection type [LoadLibraryA, ManualMap]
//2nd option - target name
//3d option - path to dll

#define LOAD_LIBRARY 1
#define MANUAL_MAP 2
DWORD FindProcessId(const char* processname);
void inject_loadlibrary(int targetPID, const char* dll_path);

int main(int argc, char** argv)
{
	int injectionType;
	DWORD targetPID;
	char* dll_path;

	injectionType = atoi(argv[1]);
    targetPID = FindProcessId(argv[2]);
	dll_path = argv[3];

	printf("DEBUG: %d, %d, %s", injectionType, targetPID, dll_path);

	switch (injectionType)
	{
	case LOAD_LIBRARY:	inject_loadlibrary(targetPID, dll_path); break;
	case MANUAL_MAP: break;
	default: return -1;
	}

	return 0;
}


void inject_loadlibrary(int targetPID, const char* dll_path)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetPID);
	LPVOID dllPathAddressInRemoteMemory = VirtualAllocEx(hProcess, NULL, strlen(dll_path), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	BOOL succeededWriting = WriteProcessMemory(hProcess, dllPathAddressInRemoteMemory, dll_path, strlen(dll_path), NULL);
	LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllPathAddressInRemoteMemory, NULL, NULL);

}


DWORD FindProcessId(const char *processname)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    DWORD result = NULL;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) return(FALSE);

    pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        printf("!!! Failed to gather information on system processes! \n");
        return(NULL);
    }

    do
    {
        //printf("Checking process %ls\n", pe32.szExeFile);
        if (0 == strcmp(processname, pe32.szExeFile))
        {
            result = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
        return result;
}