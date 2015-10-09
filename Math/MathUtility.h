#pragma once

#define PI 3.14159265358979323846f
#define TAU 6.283185307179586f
#undef min
#undef max
namespace Math {


	//Converts radians to degrees (rad * 180.f / PI)
	inline float deg(float rad) { return rad * 180.f / PI; }

	//Converts degrees to radians (deg * PI / 180.f)
	inline float rad(float deg) { return deg * PI / 180.f; }

	//Returns smaller of two numbers
	inline float min(float a, float b) { return a > b ? b : a; }

	//Returns larger of two numbers
	inline float max(float a, float b) { return a < b ? b : a; }

	//Clamps val between min and max
	inline float clamp(float val, float min, float max) { return val < min ? min : val > max ? max : val; }

	inline float isqrt(float number) {
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long *)&y;  // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		y = *(float *)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed

		return y;
	}



}