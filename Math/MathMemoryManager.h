#pragma once

#define MATH_CUSTOM_MEMORY
#include "DataTypedefs.h"
#include <assert.h>


#include "boost/pool/pool.hpp"




#ifdef MATH_CUSTOM_MEMORY
class MathMemoryManager {
public:

	static void init(U32 mat4, U32 mat4Inc, U32 mat3, U32 mat3Inc)
	{
		assert(mat4 != 0 || mat4Inc != 0 || mat3 != 0 || mat3Inc != 0);


		pool4 = new boost::pool<>(sizeof(F32) * 16, mat4Inc);

		pool3 = new boost::pool<>(sizeof(F32) * 9, mat3Inc);





	}

	static void free() {
		delete pool3;
		delete pool4;
	}

	static F32* newMat4() {
		return (F32*)pool4->malloc();
	}

	static void deleteMat4(F32* p) {
		if(p) pool4->free(p);
	}

	static F32* newMat3() {
		return (F32*)pool3->malloc();
	}

	static void deleteMat3(F32* p) {
		if (p) pool3->free(p);
	}


private:

	static boost::pool<>* pool4;
	static boost::pool<>* pool3;
};


#endif


















