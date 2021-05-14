#include "Testprogram.h"
#include "InputSystem.h"
#include <iostream>


Testprogram::Testprogram()
{
}
void Testprogram::onKeyDown(int keyPress, MessageBus* mb)
{
	
	if (keyPress == 'W')
	{
		//MessageId m = MessageId::CLOSE_MENU;
		
		//mb->postMessage(&m);
		std::cout << "W is pressed!" << std::endl;

		
	}
	else if (keyPress == 'A')
	{
		std::cout << "A is pressed!" << std::endl;

	}


}

void Testprogram::onKeyUp(int keyPress, MessageBus* mb)
{
	std::cout << "Key is up" << std::endl;
}

