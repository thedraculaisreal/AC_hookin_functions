#pragma once
#include "../source/constants.h"

class Aimbot
{

private:

	float closest_player{ -1.0f };
	float closest_pitch{ NULL };
	float closest_yaw{ NULL };

	void find_nearest_player();

public:

	void do_aimbot();

};

inline Aimbot aimbot;