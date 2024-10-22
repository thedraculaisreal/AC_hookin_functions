#include "math.h"

#define M_PI 3.14159265358979323846

float Math::euclideanDistance(float x, float y)
{
	return sqrtf((x * x) + (y * y));
}

float Math::originCalc(float x, float y)
{
	return x - y;
}

float Math::radiansToDegrees(float azimuth)
{
	return (float)(azimuth * (180.0 / M_PI));
}