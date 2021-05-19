/*#include "../src/AudioSystem/SoundDevice.h"
#include "../src/AudioSystem/SoundBuffer.h"
#include "../src/AudioSystem/SoundSource.h"
#include "../src/AudioSystem/MusicBuffer.h"*/

#include <iostream>

#include "EventSystem/MessageBus.h"
#include "ControllerSystem/ControllerSystem.h"
#include "EntityComponentSystem/Coordinator.h"
#include "AnimationSystem/AnimationSystem.h"
#include "InputSystem/InputSystem.h"

MessageBus msgBus;
Coordinator gCoordinator;

int main()
{
	InputSystem* iSys = InputSystem::getInstance();
	ControllerSystem* cSys = new ControllerSystem();
	AnimationSystem* aSys = new AnimationSystem();
	msgBus.addReciever(cSys);
	msgBus.addReciever(aSys);
}
