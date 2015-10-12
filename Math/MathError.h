#pragma once
#include <string>
#include <iostream>
#include "DataTypedefs.h"

namespace Math {

	//Prints error message
	inline void mathError(const std::string& message)
	{
		std::cout << message << std::endl;
	}

}


