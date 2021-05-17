#include "AnimationSystem.h"
#include <iostream>
#include "../EntityComponentSystem/Components/Animation.h"
#include "../EntityComponentSystem/Components/MeshRenderable.h"
#include "../EntityComponentSystem//Coordinator.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"

Coordinator gCoordinator;

AnimationSystem::AnimationSystem(MessageBus* a_msgBus) {
	msgBus = a_msgBus;
}

void AnimationSystem::handleMessage(Message* msg){
	MessageId idToCheck = MessageId::CHANGE_ANIMATION;
	if (msg->checkId(&idToCheck)) {
		ChangeAnimationMsg* changeAnimMsg = (ChangeAnimationMsg*)msg;
		auto& meshComponent = gCoordinator.getComponent<MeshRenderable>(changeAnimMsg->entity); //Get MeshRenderable component
		Ogre::AnimationState* currentAnimState = meshComponent.mesh->getAnimationState(changeAnimMsg->currentAnimationState); //Get the current animation state
		currentAnimState->setEnabled(false);

		Ogre::AnimationState* newAnimState = meshComponent.mesh->getAnimationState(changeAnimMsg->newAnimationState);
		newAnimState->setEnabled(true);
	}
}

void AnimationSystem::update(const Ogre::FrameEvent& fe){
	for (auto const& entity : m_entities) {
		auto& animation = gCoordinator.getComponent<Animation>(entity);
		animation.animationState->addTime(fe.timeSinceLastFrame);
	}
}