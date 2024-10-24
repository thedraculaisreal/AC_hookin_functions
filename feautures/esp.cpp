#include "esp.h"

void Esp::doEsp()
{
	for (const auto enemy : entlist.entities)
	{

		/*DWORD* enemyOffset = (DWORD*)(*entityList + (i * 4));
		if (!enemyOffset)
			continue;

		Entity* enemy = (Entity*)(*enemyOffset);

		if (!localPlayer)
			continue;

		if (!enemy)
			continue;

		if (enemy->health > 100 || enemy->health <= 0)
			continue;*/

		float absposX = Math::originCalc(enemy->o.x, localPlayer->o.x);
		float absposY = Math::originCalc(enemy->o.y, localPlayer->o.y);
		float absposZ = Math::originCalc(enemy->o.z, localPlayer->o.z);

		float aizimuthXY = atan2f(absposY, absposX);

		float yaw = (Math::radiansToDegrees(aizimuthXY)) + 90.0f;

		float azimuthZ = atan2f(absposZ, absposY);
		float pitch = Math::radiansToDegrees(azimuthZ);

		float localYaw = localPlayer->yaw;
		float localPitch = localPlayer->pitch;

		float yawDiff = localYaw - yaw;
		float pitchDiff = localPitch - pitch;

		yawDiff, pitchDiff = normalizeAngles(yawDiff, pitchDiff);

		int x{ xInitialization(yawDiff) };
		int y{ yInitialization(pitchDiff) };

		if (x > 1028 || x < 0 || y < 0 || y > 800) // if box is off screen dont render.
		{
			continue;
		}

		float tempDistance = Math::euclideanDistance(absposX, absposY); // calculates distance to adjust size of box

		float width { widthFormula(tempDistance) };

		float height{ heightFormula(tempDistance) };

		float healthBarHeight = (height * (enemy->health / maxHealth)); // Scale the health bar

		x = xFormula(x, tempDistance);

		gl.drawOutline(x, y, width, height, 2.0f, rgb::red); // draws from vertice to vertice using GL_LINE_STRIP in opengl

		float textPointX = gl.centerText(x, width, strlen(enemy->name) * gl.FONT_WIDTH);
		float textPointY = y - gl.FONT_HEIGHT / 2.0f;

		gl.print(textPointX, textPointY, rgb::green, "%s", enemy->name); // writes name in green text above the box

		gl.drawOutline(x - 9.5f, y, 7.0f, height, 2.0f, rgb::red);

		gl.filledBox(x - 9.0f, y, 7.0f, healthBarHeight, rgb::green);
	}
}

const int Esp::xFormula(int x, float tempDistance)
{
	x -= 50; // offset for x value

	x += 5 * (int)sqrtf(tempDistance); // formula for increasing x based on distance.

	return x;
}

const float Esp::widthFormula(float tempDistance) // formula for width, to keep box on target the right size
{
	return (250.0f / (tempDistance - 6.0f)) + 30.0f;
}

const float Esp::heightFormula(float tempDistance) // formula for height, to keep box on target the right size
{
	return (370.0f / (tempDistance - 6.0f)) + 50.0f;
}

const float Esp::normalizeAngles(float yawDiff, float pitchDiff)
{
	if (yawDiff > 180)
		yawDiff -= 360;
	if (yawDiff < -180)
		yawDiff -= yawDiff + 360;

	if (pitchDiff > 90)
		pitchDiff -= 180;
	if (pitchDiff < -90)
		pitchDiff += 180;

	return yawDiff, pitchDiff;
}

const int Esp::xInitialization(float yawDiff)
{
	return (int)(514 + (yawDiff * -10)); // 514 is half of the x value of my screen
}

const int Esp::yInitialization(float pitchDiff)
{
	return (int)(400 + (pitchDiff * 5)); // 400 is half the y value of my screen
}