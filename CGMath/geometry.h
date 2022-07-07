#pragma once
#define _USE_MATH_DEFINES
#include <cmath> 
#include "matrix.h"

namespace cgm {

	Matrix4f perspective(const float aov, const float aspect, const float near, const float far)
	{
		float t = tan(aov * 0.5 * M_PI / 180) * near;
		float b = -t;
		float r = aspect * t;
		float l = -r;

#ifndef ROW_MAJOR

		return Matrix4f{
			{2 * near / (r - l), 0, (r + l) / (r - l)},
			{0, 2 * near / (t - b), (t + b) / (t - b), 0},
			{0, 0, -(far + near) / (far - near), -2 * far * near / (far - near)},
			{0, 0, -1, 0}
		};

#else

		return Matrix4f{
			{2 * near / (r - l), 0, 0, 0},
			{0, 2 * near / (t - b), 0, 0},
			{(r + l) / (r - l), (t + b) / (t - b), -(far + near) / (far - near), -1},
			{0, 0, -2 * far * near / (far - near)}
		};

#endif // !ROW_MAJOR

	}

}