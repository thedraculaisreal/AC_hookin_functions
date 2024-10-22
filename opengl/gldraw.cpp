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
	glPopMatrix();
	glPopAttrib();
}

void GL::drawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void GL::drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);
	glEnd();
}

void GL::Font::build(int height)
{
	hdc = wglGetCurrentDC();
	base = glGenLists(96);                                                    // mono spaced font, dont need the width of every character within string
	HFONT hFont = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	bBuilt = true;
}
void GL::Font::print(float x, float y, const unsigned char color[3], const char* format, ...)
{
	glColor3ub(color[0], color[1], color[2]);
	glRasterPos2f(x, y);

	char text[100];
	va_list args;

	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

Vector3 GL::Font::centerText(float x, float y, float width, float heigt, float textWidth, float textHeight)
{
	Vector3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

float GL::Font::centerText(float x, float width, float textWidth)
{
	if (width > textWidth)
	{
		float difference = width - textWidth;
		return (x + (difference / 2));
	}
	else
	{
		float difference = textWidth - width;
		return (x - (difference / 2));
	}
}

GL::Font glFont{ NULL };

void GL::Font::draw()
{
	HDC currentHDC = wglGetCurrentDC();

	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.build(FONT_HEIGHT);
	}

	GL::setupOrtho();

	for (int i = 1; i <= numPlayers; i++)
	{

		DWORD* enemyOffset = (DWORD*)(*entityList + (i * 4));
		if (!enemyOffset)
			continue;

		Entity* enemy = (Entity*)(*enemyOffset);

		if (!localPlayer)
			continue;

		if (!enemy)
			continue;

		if (enemy->health > 100 || enemy->health <= 0)
			continue;

		float absposX = Math::originCalc(enemy->o.x, localPlayer->o.x);
		float absposY = Math::originCalc(enemy->o.y, localPlayer->o.y);
		float absposZ = Math::originCalc(enemy->o.z, localPlayer->o.z);

		float aizimuthXY = atan2f(absposY, absposX);

		float yaw = Math::radiansToDegrees(aizimuthXY);

		yaw += 90.0f;

		float azimuth_z = atan2f(absposZ, absposY);
		float pitch = Math::radiansToDegrees(absposZ);

		float localYaw = localPlayer->yaw;
		float localPitch = localPlayer->pitch;

		float yawDiff = localYaw - yaw;
		float pitchDiff = localPitch - pitch;

		if (yawDiff > 180)
			yawDiff -= 360;
		if (yawDiff < -180)
			yawDiff -= yawDiff + 360;

		if (pitchDiff > 90)
			pitchDiff -= 180;
		if (pitchDiff < -90)
			pitchDiff += 180;

		int x = (int)(512 + (yawDiff * -30));
		int y = (int)(400 + (pitchDiff * 25));

		if (x > 1028 || x < 0 || y < 0 || y > 800)
		{
			continue;
		}

		GL::drawOutline(x, y, 150, 200, 2.0f, rgb::red);
	}

	/*float textPointX = glFont.centerText(300, 200, strlen(example) * FONT_WIDTH);
	float textPointY = 300.0f - FONT_HEIGHT / 2.0f;

	glFont.print(textPointX, textPointY, rgb::green, "%s", example);

	Vector3 insideTextPoint = glFont.centerText(300, 300 + 100, 200, 200, strlen(example2) * FONT_WIDTH, FONT_HEIGHT);
	glFont.print(insideTextPoint.x, insideTextPoint.y, rgb::green, "%s", example2);
	*/

	GL::restoreGl();
}