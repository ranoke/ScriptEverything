#pragma once
#include "Lua.h"
#include <vector>
#include <iostream>

#include <lua.hpp>

template<typename T, typename W>
static void GetTable(lua_State* L, void* dst, int tableId, int count)
{
	std::vector<W> vals;
	size_t c = lua_rawlen(L, tableId);
	for (int i = 1; i <= c; i++)
	{
		lua_rawgeti(L, tableId, i);  // push t
		int top = lua_gettop(L);
		vals.push_back((W)lua_tonumber(L, top));
	}

	memcpy(dst, &vals[0], sizeof(W) * count);

}
