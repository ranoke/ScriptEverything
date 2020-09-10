#pragma once
#include "Geom.h"

namespace OpenGL
{

	void Begin();
	void DrawCrosshair(int r, int g, int b);
	void DrawRect(Rect r, glm::vec3 color, float lineWidth);
	void DrawRect(glm::vec2 center, glm::vec2 halfWH, glm::vec3 color, float lineWidth);
	glm::vec3 WorldToScreenUniversal(glm::mat4 viewmatrix, glm::vec4 viewport, glm::vec3 pos);
	glm::vec2 WorldToScreenCoustom(float* mvpmatrix, glm::vec3 pos);
	

}