#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "Config.h"
#include "Lua/Lua.h"


Config config;


int main() {
	
	

	if (cfg["DEBUG"].ToBool())
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		printf("Script Everything!\n");
	}

	Lua::Init();

	

	for (;;)
	{

	}

	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
		return TRUE;
	default:
		return FALSE;
	}
}