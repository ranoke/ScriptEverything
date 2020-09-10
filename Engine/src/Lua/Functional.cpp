#include "Functional.h"
#include <vadefs.h>
#include <Windows.h>
#include "../Renderer/OpenGL.h"

namespace Functional
{

	bool IsKeyPressed(int key)
	{
		return (bool)GetAsyncKeyState(key);
	}
	
	char Mem::ReadByte(uintptr_t addr)
	{
		return *(char*)(addr);
	}

	int Mem::ReadInt(uintptr_t addr)
	{
		return *(int*)(addr);
	}

	float Mem::ReadFloat(uintptr_t addr)
	{
		return *(float*)(addr);
	}

	std::string Mem::ReadString(uintptr_t addr)
	{
		std::string s =(const char*)(addr);
		return s;
 	}









}