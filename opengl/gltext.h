#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include "../hook/hook.h"


struct vec3
{
	float x, y, z; 
};

namespace GL
{
	class Font
	{
	public:
		bool bBuilt = false;
		unsigned int base;
		HDC hdc = nullptr;
		int height;
		int width;

		void build(int height);
		void print(float x, float y, const unsigned char color[3], const char* format, ...);

		vec3 centerText(float x, float y, float width, float heigt, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);



	};
}