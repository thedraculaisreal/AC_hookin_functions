#pragma once
#include "../source/constants.h"

class Aimbot
{

private:

	float closestPlayer{ -1.0f };
	float closestPitch{ NULL };
	float closestYaw{ NULL };

	void findNearestPlayer();

public:

	void doAimbot();

};

inline Aimbot aimbot;