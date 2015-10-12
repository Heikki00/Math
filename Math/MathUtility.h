#pragma once
#include "DataTypedefs.h"
#define PI 3.14159265358979323846f
#define TAU 6.283185307179586f
#undef min
#undef max
namespace Math {


	//Converts radians to degrees (rad * 180.f / PI)
	inline F32 deg(F32 rad) { return rad * 180.f / PI; }

	//Converts degrees to radians (deg * PI / 180.f)
	inline F32 rad(F32 deg) { return deg * PI / 180.f; }

	//Returns smaller of two numbers
	inline F32 min(F32 a, F32 b) { return a > b ? b : a; }

	//Returns larger of two numbers
	inline F32 max(F32 a, F32 b) { return a < b ? b : a; }

	//Clamps val between min and max
	inline F32 clamp(F32 val, F32 min, F32 max) { return val < min ? min : val > max ? max : val; }

	inline F32 isqrt(F32 number) {
		long i;
		F32 x2, y;
		const F32 threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long *)&y;  // evil F32ing point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		y = *(F32 *)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed

		return y;
	}



}