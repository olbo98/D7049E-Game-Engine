#include "Testprogram.h"
#include "InputSystem.h"
#include <iostream>

void Testprogram::onKeyDown(int keyPress)
{
	if (keyPress == 'W')
	{
		std::cout << "W is pressed!" << std::endl;
		
		
	}
}

void Testprogram::onKeyUp(int keyPress)
{

}

int main()
{
	//InputSystem* is = InputSystem::getInstance();
	//is->addListeners(this);
	
	//InputSystem::getInstance()->addListeners(this);
	Testprogram t;
	InputSystem* sys = InputSystem::getInstance();
	sys->addListeners(&t);

	while (true) {

		
		sys->update();
		//std::cout << "HELLO" << std::endl;
	}
}
