#pragma once
#include <string>
#include <iostream>

namespace Math{
	
	//Prints error message
	inline void mathError(const std::string& message)
	{
		std::cout << message << std::endl;
	}

}


