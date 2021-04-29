#include "System.h"
#include <cstdio>
#include <iostream>

namespace MS {
	System::System(){
		msgBus = NULL;
	}

	System::System(MessageBus* a_msgBus) {
		msgBus = a_msgBus;
	}

	void System::handleMessage(Message* msg) {
		std::cout << "Default handle message" << std::endl;
	}
}