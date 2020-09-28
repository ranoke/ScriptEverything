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

	void Mem::WriteByte(uintptr_t addr, char value)
	{
		*(char*)(addr) = value;
	}

	void Mem::WriteInt(uintptr_t addr, int value)
	{
		*(int*)(addr) = value;
	}

	void Mem::WriteFloat(uintptr_t addr, float value)
	{
		*(float*)(addr) = value;
	}

	void Mem::WriteString(uintptr_t addr, std::string value)
	{
		memcpy((void*)addr, value.c_str(), value.size());
	}

	glm::vec3 WorldToScreen(uintptr_t viewmatrix_ptr, glm::vec3 pos)	
	{
		glm::mat4 viewmatrix;
		memcpy(&viewmatrix[0], (void*)viewmatrix_ptr, 16 * sizeof(float));
		auto viewport = OpenGL::GetViewport();
		return OpenGL::WorldToScreenUniversal(viewmatrix, viewport, pos);
	}







}