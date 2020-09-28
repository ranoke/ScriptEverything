#pragma once
#include <string>
#include <glm/glm.hpp>
namespace Functional
{
	bool IsKeyPressed(int key);

	namespace Mem {
		char ReadByte(uintptr_t addr);
		int ReadInt(uintptr_t addr);
		float ReadFloat(uintptr_t addr);
		std::string ReadString(uintptr_t addr);

		void WriteByte(uintptr_t addr, char value);
		void WriteInt(uintptr_t addr, int value);
		void WriteFloat(uintptr_t addr, float value);
		void WriteString(uintptr_t addr, std::string value);
	}

	
	glm::vec3 WorldToScreen(uintptr_t viewmatrix_ptr, glm::vec3 pos);	


}

