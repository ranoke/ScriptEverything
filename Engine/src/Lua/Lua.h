#pragma once

struct lua_State;

class Lua
{
public:
	Lua();
	~Lua();

	static void Init();
	static lua_State* GetLua() { return L; }

private:
	static lua_State* L;

};

