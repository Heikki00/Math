#pragma once
#ifdef MATH_CUSTOM_MEMORY
#include "DataTypedefs.h"
#include "boost/pool/pool.hpp"

class MathMemoryManager {
public:

	static void init(U32 mat4, U32 mat4Inc, U32 mat3, U32 mat3Inc);


	static void free();

	static F32* newMat4();

	static void deleteMat4(F32* p);

	static F32* newMat3();

	static void deleteMat3(F32* p);

private:

	static boost::pool<>* pool4;
	static boost::pool<>* pool3;
};























#endif