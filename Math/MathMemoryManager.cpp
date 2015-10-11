#ifdef MATH_CUSTOM_MEMORY
#include "MathMemoryManager.h"
#include <assert.h>

boost::pool<>* MathMemoryManager::pool4 = nullptr;
boost::pool<>* MathMemoryManager::pool3 = nullptr;

void MathMemoryManager::init(U32 mat4, U32 mat4Inc, U32 mat3, U32 mat3Inc)
{
	assert(mat4 == 0 || mat4Inc == 0 || mat3 == 0 || mat3Inc == 0);
	
	pool4 = new boost::pool<>(sizeof(F32) * 16, mat4Inc);
	
	pool3 = new boost::pool<>(sizeof(F32) * 9, mat3Inc);





}

void MathMemoryManager::free()
{
	delete pool3;
	delete pool4;
}

F32* MathMemoryManager::newMat4()
{
	return (F32*)pool4->malloc();
}

void MathMemoryManager::deleteMat4(F32* p)
{
	pool4->free(p);
}

F32* MathMemoryManager::newMat3()
{
	return (F32*)pool3->malloc();
}

void MathMemoryManager::deleteMat3(F32* p)
{
	pool3->free(p);
}
#endif