#pragma once
#include <Windows.h>
#include <iostream>
#include "../Lua/Lua.h"

#include "OpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static void OnRender(HDC hDc)
{
	OpenGL::Begin();


	int args[] = { 0,0,0 };
	Lua::CallFunc("OnRender", args);

	//Rect rect({ 0,0 }, { 300,300 });
	//OpenGL::DrawCrosshair(255, 255, 0);
	////OpenGL::DrawRect(rect, { 0,255,0 }, 2.f);

	//float mat[16];
	//memcpy(mat, (void*)(0x501AE8), 16 * sizeof(float));
	//glm::mat4 matrix = glm::make_mat4(mat);
	//
	//glm::vec3 dot1 = OpenGL::WorldToScreenUniversal(matrix, { 0,0,640,480 }, { 0,0,0 });
	//glm::vec2 dot2 = OpenGL::WorldToScreenCoustom(mat, { 0,0,0 });
	//OpenGL::DrawRect({dot1.x, dot1.y}, { 10,10 }, { 255,0,0 }, 1.f);
	//OpenGL::DrawRect({dot2.x, dot2.y}, { 10,10 }, { 0,255,0 }, 1.f);

	//std::cout << "My: " << dot1.x << " " << dot1.y << " " << dot1.z << "\n";
	//std::cout << "His: " << dot2.x << " " << dot2.y << "\n";
	//
	
	
}

typedef BOOL(__stdcall* twglSwapBuffers) (_In_ HDC hDc);
static twglSwapBuffers owglSwapBuffers;
static BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc)
{
	OnRender(hDc);

	return owglSwapBuffers(hDc);
}