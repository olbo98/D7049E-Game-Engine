#include "AnimationSystem.h"
#include <iostream>

AnimationSystem::AnimationSystem(MessageBus* a_msgBus) {
	msgBus = a_msgBus;
}

void AnimationSystem::handleMessage(Message* msg){
	MessageId idToCheck = MessageId::INPUT;
	if(msg->checkId(&idToCheck)){
		std::cout << "Recieved input message" << std::endl;
	}
	//TODO: Check if the message is a state change
	//			Get the entity to change state for
	//			Get the animation component for that entity
	//			Check if the state can be transitioned to from current state(Done via the animation component?)
	//			Change state
	//			Change animation
}

/*
string activeState
string states that can be reached from current state
entity id
Ogre Entity to update current animation?
The update function would need the frame time

struct AnimationComponent{
	int entityId;
	string activeState;
	string[] allStates;
	string stateTable;
}
*/