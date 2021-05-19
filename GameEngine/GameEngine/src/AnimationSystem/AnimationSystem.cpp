#include "AnimationSystem.h"
#include <iostream>
#include "../EntityComponentSystem/Components/Animation.h"
#include "../EntityComponentSystem/Components/MeshRenderable.h"
#include "../EntityComponentSystem//Coordinator.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include "../EventSystem/Messages/ChangeStateMsg.h"

extern Coordinator gCoordinator;
extern MessageBus msgBus;

AnimationSystem::AnimationSystem() {
	
}

void AnimationSystem::handleMessage(Message* msg){
	MessageId idToCheck = MessageId::CHANGE_ANIMATION;
	if (msg->checkId(&idToCheck)) {
		ChangeAnimationMsg* changeAnimMsg = (ChangeAnimationMsg*)msg;

		Entity entity = changeAnimMsg->entity; //Get the entity id
		auto& meshComponent = gCoordinator.getComponent<MeshRenderable>(entity); //Get MeshRenderable component
		Ogre::Entity* mesh = meshComponent.mesh; //Get the ogre mesh
		string currentState = changeAnimMsg->currentAnimationState;

		Ogre::AnimationState* currentAnimState = mesh->getAnimationState(currentState); //Get the current animation state
		currentAnimState->setEnabled(false); //Diable current animation
		Ogre::AnimationState* newAnimState = mesh->getAnimationState(changeAnimMsg->newAnimationState); //Get the new animation
		newAnimState->setEnabled(true); //Enable the new animation
	}
}

void AnimationSystem::update(const Ogre::FrameEvent& fe){
	for (auto const& entity : m_entities) {
		auto& animationComponent = gCoordinator.getComponent<Animation>(entity);
		animationComponent.animation->addTime(fe.timeSinceLastFrame);
		if (animationComponent.animation->hasEnded()) {
			ChangeStateMsg changeAnimMsg = ChangeStateMsg(State::IDLE);
		}
	}
}