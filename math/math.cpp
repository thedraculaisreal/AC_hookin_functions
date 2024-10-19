#include "math.h"

#define M_PI 3.14159265358979323846

float Math::euclidean_distance(float x, float y)
{
	return sqrtf((x * x) + (y * y));
}

float Math::origin_calc(float x, float y)
{
	return x - y;
}

float Math::radians_to_degrees(float azimuth)
{
	return (float)(azimuth * (180.0 / M_PI));
}