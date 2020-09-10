#pragma once
#include <string>
namespace Functional
{
	bool IsKeyPressed(int key);

	namespace Mem {
		char ReadByte(uintptr_t addr);
		int ReadInt(uintptr_t addr);
		float ReadFloat(uintptr_t addr);
		std::string ReadString(uintptr_t addr);
	}



}

