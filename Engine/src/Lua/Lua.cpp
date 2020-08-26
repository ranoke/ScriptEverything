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
    printf("Initializing Lua..\n");
    L = luaL_newstate();                       
    luaL_openlibs(L);                           

    if (luaL_loadfile(L, CONFIG_DIR "main.lua"))
    {

        printf("Failed to load lua main.lua file\n");
    }


    if (lua_pcall(L, 0, 0, 0))
    {
        printf("Failed to pcall()\n");
    }
        

    int args[] = { 0,0,0 };
    CallFunc("main", args);


	
}

void Lua::CallFunc(const char* func, int* args)
{
    lua_getglobal(L, func);
    if (lua_pcall(L, args[0], args[1], args[2]))
        printf("Failed to pcall function\n");
}