#include "aimbot.h"

void Aimbot::findNearestPlayer()
{
	closestPlayer = -1.0f;

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

		if (absposY < 0)
		{
			absposY *= -1;
		}
		if (absposY < 5)
		{
			if (absposX < 0)
			{
				absposX *= -1;
			}
			absposY = absposX;
		}

		float azimuthZ = atan2f(absposZ, absposY);
		float pitch = Math::radiansToDegrees(azimuthZ);

		float tempDistance = Math::euclideanDistance(absposX, absposY);

		if (closestPlayer == -1.0f || tempDistance < closestPlayer)
		{
			closestPlayer = tempDistance;
			closestYaw = yaw + 90.0f;
			closestPitch = pitch;
		}

	}

}

void Aimbot::doAimbot()
{
	findNearestPlayer();

	if (!GetAsyncKeyState(VK_XBUTTON2))
		return;

	Sleep(1);

	localPlayer->pitch = closestPitch;
	localPlayer->yaw = closestYaw;
}