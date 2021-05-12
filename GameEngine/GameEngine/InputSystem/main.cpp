#include "Testprogram.h"
#include "InputSystem.h"
#include <Windows.h>

int main()
{
	Testprogram test;
	InputSystem* sys = InputSystem::getInstance();
	sys->addListeners(&test);

	while (true) {

		sys->update();
		Sleep(150);

	}
}