//#include "Test.h"
//#include <iostream>
//#include <Windows.h>
//#include "../EntityComponentSystem/Coordinator.h"
//#include "../EventSystem/MessageBus.h"
//#include "../RenderSystem/WindowManager.h"
//
//Coordinator gCoordinator;
//MessageBus msgBus;
//WindowManager gWindManager;
//
//void Test::onKeyDown(int keyPress)
//{
//	
//	if (keyPress == 'A') {
//		std::cout << "KEY DOWN" << std::endl;
//	}
//}
//
//void Test::onKeyUp(int keyPress)
//{
//	std::cout << "KEY UP" << std::endl;
//}
//
//int main() {
//	Test t;
//	InputSystem* inp = InputSystem::getInstance();
//	inp->addListeners(&t);
//
//	while(true){
//		inp->update();
//		//Sleep(100);
//	}
//
//
//}