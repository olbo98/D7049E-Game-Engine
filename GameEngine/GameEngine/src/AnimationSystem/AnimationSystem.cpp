#include "AnimationSystem.h"


extern Coordinator gCoordinator;
extern MessageBus msgBus;

void AnimationSystem::Init() {

}

void AnimationSystem::handleMessage(Message* msg){
	MessageId idToCheck = MessageId::CHANGE_ANIMATION;
	if (msg->checkId(&idToCheck)) {
		ChangeAnimationMsg* changeAnimMsg = (ChangeAnimationMsg*)msg;

		//Entity entity = changeAnimMsg->entity; //Get the entity id
		//auto& meshComponent = gCoordinator.getComponent<MeshRenderable>(entity); //Get MeshRenderable component
		//Ogre::Entity* mesh = meshComponent.mesh; //Get the ogre mesh
		//string currentState = changeAnimMsg->currentAnimationState;
		//string newState = changeAnimMsg->newAnimationState;
		//
		//Ogre::AnimationState* currentAnimState = mesh->getAnimationState(currentState); //Get the current animation state
		//currentAnimState->setEnabled(false); //Diable current animation
		//Ogre::AnimationState* newAnimState = mesh->getAnimationState(newState); //Get the new animation
		//newAnimState->setEnabled(true); //Enable the new animation

		//auto& animComponent = gCoordinator.getComponent<Animation>(entity);
		//animComponent.animation = newAnimState;

		Entity entity = changeAnimMsg->entity; //Get the entity id
		string newAniamtion = changeAnimMsg->newAnimationState;
		changeAnim(entity, newAniamtion);
	}
}

void AnimationSystem::changeAnim(Entity entity, string newAnimation) {
	auto& meshComponent = gCoordinator.getComponent<MeshRenderable>(entity);
	auto& animComponent = gCoordinator.getComponent<Animation>(entity);
	Ogre::Entity* mesh = meshComponent.mesh;
	Ogre::AnimationState* anim = animComponent.animation;

	anim->setEnabled(false);
	Ogre::AnimationState* newAnimState = mesh->getAnimationState(newAnimation); //Get the new animation
	newAnimState->setEnabled(true); //Enable the new animation
	animComponent.animation = newAnimState;
}

void AnimationSystem::Update(const Ogre::FrameEvent& fe){
	for (auto const& entity : m_entities) {
		auto& animationComponent = gCoordinator.getComponent<Animation>(entity);
		animationComponent.animation->addTime(fe.timeSinceLastFrame);
		if (animationComponent.animation->hasEnded()) {
			animationComponent.animation->setTimePosition(0); // Reset animation time
			ChangeStateMsg changeStateMsg = ChangeStateMsg(State::IDLE, entity);

			changeAnim(entity, "Idle");
			msgBus.postMessage(&changeStateMsg);
		}
	}
}