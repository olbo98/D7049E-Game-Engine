#include "libclass.h"
#include <iostream>

using namespace LOGGING;

void libclass::test_function(int x, int y)
{
	int result = x + y;
	std::cout << result << std::endl;
	std::cin.get();
};