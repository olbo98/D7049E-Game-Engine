#include "Testprogram.h"
#include "InputSystem.h"
#include <iostream>

void Testprogram::onKeyDown(int keyPress)
{
	
	if (keyPress == 'W')
	{
		std::cout << "W is pressed!" << std::endl;
		
	}
	else if (keyPress == 'A')
	{
		std::cout << "A is pressed!" << std::endl;

	}
}

void Testprogram::onKeyUp(int keyPress)
{
	std::cout << "Key is up" << std::endl;
}

