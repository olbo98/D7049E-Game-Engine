#include "Testprogram.h"
#include "InputSystem.h"
#include "../EventSystem/MessageBus.h"
#include <Windows.h>

int main()
{
	MessageBus* mb = new MessageBus();
	Testprogram* test = new Testprogram();
	InputSystem* sys = InputSystem::getInstance();

	sys->addListeners(test);
	sys->setMsgBus(mb);

	mb->addReciever(sys);

	while (true) {

		sys->update();
		mb->notify();
		Sleep(150);

	}
}