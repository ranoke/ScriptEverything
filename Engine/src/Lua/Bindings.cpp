#include "Bindings.h"
#include "Lua.h"
#include "Functional.h"

#include "../Base.h"

#include <assert.h>
#include <map>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>


#include <glm/glm.hpp>
#include "Helper.h"

#include "../Renderer/OpenGL.h"






typedef int (*lua_CFunction) (lua_State* L);
static int LuaPrint(lua_State* L);
static int LuaPrintInt(lua_State* L);
static int LuaGetModule(lua_State* L);
static int LuaReadMemory(lua_State* L);
static int LuaReadMemoryInt(lua_State* L);
static int LuaWriteMemoryInt(lua_State* L);
static int LuaIsKeyPressed(lua_State* L);
static int LuaPrintVec3(lua_State* L);
static int LuaDrawRectC(lua_State* L);
static int LuaWorldToScreen(lua_State* L);


Bindings::Bindings()
{
}

Bindings::~Bindings()
{
}

void Bindings::Bind()
{
	lua_State* L = Lua::GetLua();

	using namespace luabridge;

	getGlobalNamespace(L)
		.addFunction<bool, int>("IsKeyPressed", &Functional::IsKeyPressed)
	.beginNamespace("Renderer")
		.addFunction<void, int,int,int>("DrawCrosshair", &OpenGL::DrawCrosshair)
	.endNamespace()

	.beginNamespace("Mem")
		.addFunction<char, uintptr_t>("ReadByte", &Functional::Mem::ReadByte)
		.addFunction<int, uintptr_t>("ReadInt", &Functional::Mem::ReadInt)
		.addFunction<float, uintptr_t>("ReadFloat", &Functional::Mem::ReadFloat)
		.addFunction<std::string, uintptr_t>("ReadString", &Functional::Mem::ReadString)
		.addFunction<void, uintptr_t, char>("WriteByte", &Functional::Mem::WriteByte)
		.addFunction<void, uintptr_t, int>("WriteInt", &Functional::Mem::WriteInt)
		.addFunction<void, uintptr_t, float>("WriteFloat", &Functional::Mem::WriteFloat)
		.addFunction<void, uintptr_t, std::string>("WriteString", &Functional::Mem::WriteString)
	.endNamespace();

	assert(L && "Failed to do Lua for bindings!");
	lua_register(L, "Print", LuaPrint);
	lua_register(L, "PrintInt", LuaPrintInt);
	lua_register(L, "GetModule", LuaGetModule);
	lua_register(L, "WriteMemoryInt", LuaWriteMemoryInt);
	lua_register(L, "PrintVec", LuaPrintVec3);
	lua_register(L, "DrawRectC", LuaDrawRectC);
	lua_register(L, "WorldToScreen", LuaWorldToScreen);


}


static int LuaPrint(lua_State* L)
{
	std::cout << lua_tostring(L, 1) << std::endl;
	return 0;
}

static int LuaPrintInt(lua_State* L)
{
	std::cout << lua_tointeger(L, 1) << std::endl;
	return 0;
}

//args: vec3
static int LuaPrintVec3(lua_State* L)
{
	int i, n;
	luaL_checktype(L,1, LUA_TTABLE);
	
	i = lua_rawlen(L, 1);  
	

	return 0;
}

// Draw rect by center
//args: vec2 center, vec2 half_width_height, vec3 color, float lineWidth
static int LuaDrawRectC(lua_State* L)
{
	glm::vec2 center, halfWH;
	glm::vec3 color;
	float lineWidth;

	int n = lua_gettop(L);
	assert(n == 4 && "LuaDrawRectC bad argument count!");


	GetTable<glm::vec2, float>(L, &center, 1, 2);
	GetTable<glm::vec2, float>(L, &halfWH, 2, 2);
	GetTable<glm::vec3, float>(L, &color, 3, 3);
	lineWidth = (float)lua_tonumber(L, 4);
	OpenGL::DrawRect(center, halfWH, color, lineWidth);


		
	return 0;
}

//args: std::string moduleName
static int LuaGetModule(lua_State* L)
{
	std::string module = lua_tostring(L, 1);
	uintptr_t moduleH = (uintptr_t)GetModuleHandle(module.c_str());
	//std::cout << moduleH << "\n";
	lua_pushnumber(L, moduleH);
	return 1;
}

//args: module, memoryAddr, std::string type
static int LuaReadMemory(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 3 && "LuaReadMemory bad argument count!");
	uintptr_t module = lua_tonumber(L, 1);
	uintptr_t addr = lua_tonumber(L, 2);
	std::string type = lua_tostring(L, 3);
	
	int ret = *(int*)(module + addr);

	/*switch (string2type(type.c_str()))
	{
	case DataType::INT: ret = 
	case DataType::FLOAT: ret = (float*)(module + addr); break;
	}*/

	lua_pushnumber(L, ret);
	return 1;
}

static int LuaReadMemoryInt(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2 && "LuaReadMemory bad argument count!");
	uintptr_t module = lua_tonumber(L, 1);
	uintptr_t addr = lua_tonumber(L, 2);
	int ret = *(int*)(module + addr);
	lua_pushnumber(L, ret);
	return 1;
}

static int LuaWriteMemoryInt(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 3 && "LuaReadMemory bad argument count!");
	uintptr_t module = lua_tonumber(L, 1);
	uintptr_t addr = lua_tonumber(L, 2);
	int val = lua_tonumber(L, 3);
	*(int*)(module + addr) = val;
	return 0;
}

//args: keycode
static int LuaIsKeyPressed(lua_State* L)
{
	GetAsyncKeyState(VK_ADD);
	int n = lua_gettop(L);
	assert(n == 1 && "LuaIsKeyPressed bad argument count!");
	lua_pushboolean(L, GetAsyncKeyState(lua_tonumber(L, 1)));
	return 1;
}

static int LuaWorldToScreen(lua_State* L)
{
	int n = lua_gettop(L);
	assert(n == 2 && "LuaWorldToScreen bad argument count!");
	uintptr_t viewmatrix_ptr = lua_tonumber(L, 1);
	glm::vec3 pos;
	GetTable<glm::vec3, float>(L, &pos, 2, 3);
	glm::vec3 ret = Functional::WorldToScreen(viewmatrix_ptr, pos);

	lua_pushnumber(L, ret[0]);
	lua_pushnumber(L, ret[1]);

	return 2;
}



