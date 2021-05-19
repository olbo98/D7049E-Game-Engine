#include "ControllerSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/PlayerId.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include <string>

using namespace std;

extern Coordinator gCoordinator;
extern MessageBus msgBus;

void ControllerSystem::onKeyDown(int keyPress)
{
	Entity firstPlayerEnt;
	Entity secondPlayerEnt;

	for (auto const& entity : m_entities) {
		auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(entity);
		if (playerIdComponent.playerId == 1) {
			firstPlayerEnt = entity;
		}

		if (playerIdComponent.playerId == 2) {
			secondPlayerEnt = entity;
		}
	}

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
		State currentState = player1Fsm.getCurrentState();
		string stateAsString = player1Fsm.getStateAsString(stateToChangeTo);
		string currentStateAsString = player1Fsm.getStateAsString(currentState);

		if (player1Fsm.changeState(stateToChangeTo)) {
			auto& transformComponent = gCoordinator.getComponent<Transform>(firstPlayerEnt);
			Vec3 velocity = Vec3(-1.0, 0.0, 0.0);
			transformComponent.position += velocity;
			ChangeAnimationMsg changeAnimMsg = ChangeAnimationMsg(stateAsString, currentStateAsString, firstPlayerEnt);
			msgBus.postMessage(&changeAnimMsg);
		}
		//create message and send to animation to start walking back anim
		//move transform to the left
	}
	case 68://D
		//create message and send to animation to start walking forward anim
		//move transform to the right
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
