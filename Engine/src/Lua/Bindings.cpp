#include "Bindings.h"
#include "Lua.h"

#include "../Base.h"

#include <assert.h>
#include <map>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

//enum DataType {
//	NONE = 0,
//	INT = 1,
//	FLOAT = 2
//};
//
//const std::map<const char*, DataType> string2typeEnum{
//		{ "int", DataType::INT },
//		{ "float", DataType::FLOAT }
//};
//
//int string2type(const char* e)
//{
//	auto   it = string2typeEnum.find(e);
//	return it->second;
//}

typedef int (*lua_CFunction) (lua_State* L);
static int average(lua_State* L);
static int LuaPrint(lua_State* L);
static int LuaPrintInt(lua_State* L);
static int LuaGetModule(lua_State* L);
static int LuaReadMemory(lua_State* L);
static int LuaReadMemoryInt(lua_State* L);
static int LuaWriteMemoryInt(lua_State* L);
static int LuaIsKeyPressed(lua_State* L);

Bindings::Bindings()
{
}

Bindings::~Bindings()
{
}

void Bindings::Bind()
{
	lua_State* L = Lua::GetLua();
	assert(L && "Failed to get Lua for bindings!");
	lua_register(L, "Print", LuaPrint);
	lua_register(L, "PrintInt", LuaPrintInt);
	lua_register(L, "average", average);
	lua_register(L, "GetModule", LuaGetModule);
	lua_register(L, "ReadMemory", LuaReadMemory);
	lua_register(L, "ReadMemoryInt", LuaReadMemoryInt);
	lua_register(L, "WriteMemoryInt", LuaWriteMemoryInt);
	lua_register(L, "IsKeyPressed", LuaIsKeyPressed);
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

static int average(lua_State* L)
{
	/* get number of arguments */
	int n = lua_gettop(L);
	double sum = 0;
	int i;

	/* loop through each argument */
	for (i = 1; i <= n; i++)
	{
		/* total the arguments */
		sum += lua_tonumber(L, i);
	}

	/* push the average */
	lua_pushnumber(L, sum / n);

	/* push the sum */
	lua_pushnumber(L, sum);

	/* return the number of results */
	return 2;
}

//args: std::string moduleName
static int LuaGetModule(lua_State* L)
{
	std::string module = lua_tostring(L, 1);
	uintptr_t moduleH = (uintptr_t)GetModuleHandle(s2ws(module).c_str());
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



