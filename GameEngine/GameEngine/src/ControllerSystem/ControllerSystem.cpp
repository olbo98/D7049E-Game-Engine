#include "ControllerSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/PlayerId.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include <string>

using namespace std;

extern Coordinator gCoordinator;
extern MessageBus msgBus;

ControllerSystem::ControllerSystem() {
	velocity = 10;
	setPlayerEntityIds();
}

void ControllerSystem::setPlayerEntityIds() {
	for (auto const& entity : m_entities) {
		auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(entity);
		if (playerIdComponent.playerId == 1) {
			firstPlayerEnt = entity;
		}

		if (playerIdComponent.playerId == 2) {
			secondPlayerEnt = entity;
		}
	}
}

void ControllerSystem::moveEntity(Entity entityToMove, Vec3 a_velocity) {
	auto& transformComponent = gCoordinator.getComponent<Transform>(entityToMove);
	Vec3 position = transformComponent.node->getPosition();
	position += a_velocity;
	transformComponent.node->setPosition(position.toOgre());
}

void ControllerSystem::notifyAnimationSystem(string newState, string currentState, Entity a_entity) {
	ChangeAnimationMsg changeAnimMsg = ChangeAnimationMsg(newState, currentState, a_entity);
	msgBus.postMessage(&changeAnimMsg);
}

void ControllerSystem::handleHorizontalMove(State stateToChangeTo, PlayerFSM stateMachine, Entity playerToMove, float xDirection) {
	State currentState = stateMachine.getCurrentState();
	string stateAsString = stateMachine.getStateAsString(stateToChangeTo);
	string currentStateAsString = stateMachine.getStateAsString(currentState);

	if (stateMachine.changeState(stateToChangeTo)) {
		Vec3 directionVector = Vec3(xDirection, 0, 0);
		moveEntity(playerToMove, directionVector * velocity);
		notifyAnimationSystem(stateAsString, currentStateAsString, playerToMove);
	}
}

void ControllerSystem::onKeyDown(int keyPress)
{
	switch (keyPress)
	{
	case 87://W
		//create message and send to animation to start jumping anim
		//Move transform up?
	case 83://S
		//create message and send to animation to start crouch anim
	case 65://A
	{
		State stateToChangeTo = State::WALKING_BCK;
		handleHorizontalMove(stateToChangeTo, player1Fsm, firstPlayerEnt, -1);
	}
	case 68://D
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player1Fsm, firstPlayerEnt, 1);
	}
	case 32://Space
		//Create message and send to animation to start jumping animation
		//Move transform up?
	default:
		break;
	}
}

void ControllerSystem::onKeyUp(int keyPress)
{
}

void ControllerSystem::handleMessage(Message* msg)
{
}

void ControllerSystem::Update(const Ogre::FrameEvent& fe) {

}
