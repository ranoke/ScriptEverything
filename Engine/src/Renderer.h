#pragma once
#include <Windows.h>
#include <iostream>
#include "Lua/Lua.h"



static void OnRender(HDC hDc)
{
	int args[] = { 0,0,0 };
	Lua::CallFunc("OnRender", args);
	

}

typedef BOOL(__stdcall* twglSwapBuffers) (_In_ HDC hDc);
static twglSwapBuffers owglSwapBuffers;
static BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc)
{
	OnRender(hDc);

	return owglSwapBuffers(hDc);
}