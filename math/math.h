#pragma once
#include <cstdio>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>

namespace Math
{
	float euclidean_distance(float x, float y);
	float origin_calc(float x, float y);
	float radians_to_degrees(float azimuth);
}

class Vector3
{
public:

	float x;
	float y;
	float z;

};