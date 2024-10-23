#pragma once
#include "../opengl/gldraw.h"


class Esp
{

private:

	const float maxHealth = 100.0f;  // max health value

	const int xFormula(int x, float tempDistance);

	const float widthFormula(float tempDistance);

	const float heightFormula(float tempDistance);

	const float normalizeAngles(float yawDiff, float pitchDiff);

	const int xInitialization(float yawDiff);

	const int yInitialization(float pitchDiff);

public:

	void doEsp();

};

inline Esp esp;

