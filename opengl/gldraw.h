#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include "../hook/hook.h"
#include "../math/math.h"
#include "../source/constants.h"

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
}

namespace GL
{
	void setupOrtho();
	void restoreGl();

	void drawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
	void drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);

	class Font
	{
	public:

		bool bBuilt = false;
		unsigned int base{ 0 };
		HDC hdc = nullptr;
		int height{ 0 };
		int width{ 0 };

		const int FONT_HEIGHT{ 15 };
		const int FONT_WIDTH{ 9 };

		const char* example = "ESP Box";
		const char* example2 = "I'm inside";

		void draw();

		void build(int height);
		void print(float x, float y, const unsigned char color[3], const char* format, ...);

		Vector3 centerText(float x, float y, float width, float heigt, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);
	};

	inline Font font;
}
