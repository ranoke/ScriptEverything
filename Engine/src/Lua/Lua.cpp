#include "Lua.h"
#include "../Base.h"
#include "Bindings.h"

#include <iostream>

// include Lua, assumes it is local to this file
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

lua_State* Lua::L;

Lua::Lua()
{
}

Lua::~Lua()
{
	/* cleanup Lua */
	lua_close(L);
}

void Lua::Init() 
{
	std::cout << "Initializing Lua..\n";
	L = luaL_newstate();

	// Add standard libraries to Lua Virtual Machine
	luaL_openlibs(L);


	std::cout << "Binding lua functionality..\n";
	Bindings::Bind();

	std::cout << "Loading lua script..\n";
	luaL_dofile(L, CONFIG_DIR"main.lua");

	
}