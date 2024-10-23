#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include "../hook/hook.h"
#include "../math/math.h"
#include "../source/constants.h"
#include "../feautures/esp.h"

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
}

class GL
{

private:

    void setupOrtho(); // Sets up orthographic projection for 2D rendering.
    void restoreGl(); // Restores OpenGL state after rendering.

    void build(int height); // Initializes OpenGL context/resources.

    bool bBuilt = false; // Flag indicating if the OpenGL context has been built.
    unsigned int base{ 0 }; // Font base for text rendering.
    HDC hdc = nullptr; // Handle to the device context for Windows.
    int height{ 0 }; // Height of the rendering area.
    int width{ 0 }; // Width of the rendering area.

public:

    const int FONT_HEIGHT{ 15 }; // Default font height.
    const int FONT_WIDTH{ 9 }; // Default font width.

    void print(float x, float y, const unsigned char color[3], const char* format, ...);
    void draw(); // Triggers the rendering process.
    void filledBox(float x, float y, float width, float height, const GLubyte color[3]) const;
    void drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]) const;
    void drawLine(float localX, float localY, float enemyX, float enemyY, float lineWidth, const GLubyte color[3]) const;
    Vector3 centerText(float x, float y, float width, float height, float textWidth, float textHeight) const;
    float centerText(float x, float width, float textWidth) const; // Centers text horizontally.
};

inline GL gl; // Global instance of GL class.
