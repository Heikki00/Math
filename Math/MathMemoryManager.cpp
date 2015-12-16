
#include "MathMemoryManager.h"

#ifdef MATH_CUSTOM_MEMORY

boost::pool<>* MathMemoryManager::pool4 = nullptr;
boost::pool<>* MathMemoryManager::pool3 = nullptr;

#endif



