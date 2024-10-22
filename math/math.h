#pragma once
#include <cstdio>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>

namespace Math
{
	float euclideanDistance(float x, float y);
	float originCalc(float x, float y);
	float radiansToDegrees(float azimuth);
}

class Vector3
{
public:

	float x;
	float y;
	float z;

};