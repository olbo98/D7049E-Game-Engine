#include "AnimationSystem.h"
#include <iostream>

AnimationSystem::AnimationSystem(MessageBus* a_msgBus) {
	msgBus = a_msgBus;
}

void AnimationSystem::handleMessage(Message* msg){
	if(msg->checkId(MessageId::INPUT)){
		std::cout << "Recieved input message" << std::endl;
	}
	//TODO: Check if the message is a state change
	//			Get the entity to change state for
	//			Get the animation component for that entity
	//			Check if the state can be transitioned to from current state(Done via the animation component?)
	//			Change state
	//			Change animation
}