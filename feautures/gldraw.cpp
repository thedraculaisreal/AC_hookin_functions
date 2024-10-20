#include "gldraw.h"

void GL::setupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}
void GL::restoreGl()
{

}

void GL::drawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{

}
void GL::drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{

}