#pragma once
#include "Base.h"

enum class RenderHook {
	None,
	OpenGL  = 1,
	DirectX = 2
};


class Hooks
{
public:
	static void Init(RenderHook renderer);
	static void Remove();

	static RenderHook render;
};

