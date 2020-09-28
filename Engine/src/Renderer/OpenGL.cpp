#include "OpenGL.h"

#include <Windows.h>
#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace OpenGL
{
	GLfloat tmp_viewport[4];

	void Begin()
	{
		glPushMatrix();
		glGetFloatv(GL_VIEWPORT, tmp_viewport);

		glViewport(0, 0, tmp_viewport[2], tmp_viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, tmp_viewport[2], tmp_viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void DrawCrosshair(int r, int g, int b)
	{
		glColor3ub(r, g, b);//white
		glLineWidth(2.0);

		//GLfloat tmp_viewport[4];
		glGetFloatv(GL_VIEWPORT, tmp_viewport);

		int crossHair[8] = { tmp_viewport[2] / 2 - 7, tmp_viewport[3] / 2,// horizontal line
			tmp_viewport[2] / 2 + 7, tmp_viewport[3] / 2,
			tmp_viewport[2] / 2, tmp_viewport[3] / 2 + 7, //vertical line
			tmp_viewport[2] / 2, tmp_viewport[3] / 2 - 7 };

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_INT, 0, crossHair);
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	void DrawRect(Rect r, glm::vec3 color, float lineWidth)
	{
		glColor3ub(color.x, color.y, color.z);

		glm::vec2 vertices[4] = { r.topleft, {r.botright.x, r.topleft.y}, r.botright, {r.topleft.x, r.botright.y} };
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	void DrawRect(glm::vec2 center, glm::vec2 halfWH, glm::vec3 color, float lineWidth)
	{
		glColor3ub(color.x, color.y, color.z);
		glm::vec2 vertices[4] = {
			{center.x - halfWH.x, center.y + halfWH.y},
			{center.x + halfWH.x, center.y + halfWH.y},
			{center.x + halfWH.x, center.y - halfWH.y},
			{center.x - halfWH.x, center.y - halfWH.y}
		};
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	glm::vec3 WorldToScreenUniversal(glm::mat4 viewmatrix, glm::vec4 viewport, glm::vec3 pos)
	{
		glm::mat4 modelmatix = glm::translate(viewmatrix, glm::vec3(0.0f, 0.0f, 0.0f));

		return glm::project(pos, modelmatix, viewmatrix, viewport);
	}

	glm::vec2 WorldToScreenCoustom(float* mvpmatrix, glm::vec3 pos)
	{
		//Matrix-Vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		glm::vec4 clipCoords;
		clipCoords.x = pos.x * mvpmatrix[0] + pos.y * mvpmatrix[4] + (pos.z) * mvpmatrix[8] + mvpmatrix[12];
		clipCoords.y = pos.x * mvpmatrix[1] + pos.y * mvpmatrix[5] + (pos.z) * mvpmatrix[9] + mvpmatrix[13];
		clipCoords.z = pos.x * mvpmatrix[2] + pos.y * mvpmatrix[6] + (pos.z) * mvpmatrix[10] + mvpmatrix[14];
		clipCoords.w = pos.x * mvpmatrix[3] + pos.y * mvpmatrix[7] + (pos.z) * mvpmatrix[11] + mvpmatrix[15];

		//perspective division, dividing by clip.W = NDC = Normalized Device Coordinates
		glm::vec3 ndc;
		ndc.x = clipCoords.x / clipCoords.w;
		ndc.y = clipCoords.y / clipCoords.w;
		ndc.z = clipCoords.z / clipCoords.w;

		//viewport tranform to screenCooords
		GLfloat tmpViewPort[4] = { 0 };
		glGetFloatv(GL_VIEWPORT, tmpViewPort); // viewport = (0, 0, width, height)

		glm::vec2 playerScreenCoords;
		playerScreenCoords.x = (tmpViewPort[2] / 2 * ndc.x) + (ndc.x + tmpViewPort[2] / 2);
		playerScreenCoords.y = -(tmpViewPort[3] / 2 * ndc.y) + (ndc.y + tmpViewPort[3] / 2);
		return playerScreenCoords;
	}

	glm::vec4 GetViewport()
	{
		glm::vec4 viewport = { 0,0,0,0 };
		glGetFloatv(GL_VIEWPORT, &viewport[0]);
		return viewport;
	}

}