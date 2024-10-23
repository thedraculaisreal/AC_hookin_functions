#include "gldraw.h"

void GL::setupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS); // push server attribute stack, GL_ALL_ATTRIB_BITS saves all stackable states
	glPushMatrix(); // pushes the current matrix stack down by one
	GLint viewport[4]; // Now, viewport contains the values:
	// viewport[0] = x position of the lower-left corner
	// viewport[1] = y position of the lower-left corner
	// viewport[2] = width of the viewport
	// viewport[3] = height of the viewport
	glGetIntegerv(GL_VIEWPORT, viewport); // takes viewport settings and stores them in the viewport array
	glViewport(0, 0, viewport[2], viewport[3]); // sets viewport from screen coordinates
	glMatrixMode(GL_PROJECTION); // applies matrix operations to the stack for projection
	glLoadIdentity(); // replace the current matrix with the identity matrix
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1); // multiply the current matrix with an orthographic matrix
	glMatrixMode(GL_MODELVIEW); // applies subsequent matrix operations to the modelview matrix stack
	glLoadIdentity(); // replace the current matrix with the identity matrix
	glDisable(GL_DEPTH_TEST); // disables depth testing
}
void GL::restoreGl()
{
	glPopMatrix(); // pops the current matrix stack, replacing the current matrix with the one below it on the stack
	glPopAttrib(); // restores the values of the state variables saved with the last glPushAttrib command
}

void GL::filledBox(float x, float y, float width, float height, const GLubyte color[3]) const
{

	glBegin(GL_QUADS);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x, y); // each vertex connects to the one created afterwards.
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void GL::drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]) const
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x , y ); // each vertex connects to the one created afterwards.
	glVertex2f(x + width , y );
	glVertex2f(x + width , y + height );
	glVertex2f(x , y + height );
	glVertex2f(x , y );
	glEnd();
}

void GL::build(int height)
{
	hdc = wglGetCurrentDC(); // handle to device context associated with opengl
	base = glGenLists(96);   // mono spaced font, dont need the width of every character within string
	HFONT hFont = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	bBuilt = true;
}

void GL::print(float x, float y, const unsigned char color[3], const char* format, ...)
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

Vector3 GL::centerText(float x, float y, float width, float heigt, float textWidth, float textHeight) const
{
	Vector3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

float GL::centerText(float x, float width, float textWidth) const
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


void GL::draw()
{
	HDC currentHDC = wglGetCurrentDC();

	if (!bBuilt || currentHDC != hdc)
	{
		build(FONT_HEIGHT);
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

		float azimuthZ = atan2f(absposZ, absposY);
		float pitch = Math::radiansToDegrees(azimuthZ);

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

		int x = (int)(514 + (yawDiff * -10)); // 514 is half of the x value of my screen
		int y = (int)(400 + (pitchDiff * 5)); // 400 is half the y value of my screen

		if (x > 1028 || x < 0 || y < 0 || y > 800) // if box is off screen dont render.
		{
			continue;
		}

		float tempDistance = Math::euclideanDistance(absposX, absposY); // calculates distance to adjust size of box

		float width;

		float height;

		width = (250.0f / (tempDistance - 6.0f)) + 30.0f; // formula for width, to keep box on target the right size
		height = (370.0f / (tempDistance - 6.0f)) + 50.0f; // formula for height, to keep box on target the right size

		float maxHealth = 100.0f;  // max health value
		float healthBarHeight = (height * (enemy->health / maxHealth)); // Scale the health bar

		x -= 50; // offset for x value

		x += 5 * (int)sqrtf(tempDistance); // formula for increasing x based on distance.

		GL::drawOutline(x, y, width, height, 2.0f, rgb::red); // draws from vertice to vertice using GL_LINE_STRIP in opengl
		
		float textPointX = centerText(x, width, strlen(enemy->name) * FONT_WIDTH); 
		float textPointY = y - FONT_HEIGHT / 2.0f;

		print(textPointX, textPointY, rgb::green, "%s", enemy->name); // writes name in green text above the box

		GL::drawOutline(x - 9.5f, y, 7.0f, height, 2.0f, rgb::red);

		GL::filledBox(x - 9.0f, y, 7.0f, healthBarHeight, rgb::green);
	}

	GL::restoreGl();
}