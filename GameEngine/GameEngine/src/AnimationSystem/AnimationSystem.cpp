#include "AnimationSystem.h"
#include <iostream>
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/Animation.h"

extern Coordinator gCoordinator;

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

void update(const Ogre::FrameEvent& fe){
	for (auto const& entity : mEntities){
		auto& animation = gCoordinator.getComponent<Animation>(entity);
		animation.animationState->addTime(fe.timeSinceLastFrame);
	}
}