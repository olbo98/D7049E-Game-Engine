#include "ControllerSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/PlayerId.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include "../EventSystem/Messages/ChangeStateMsg.h"
#include "../EventSystem/Messages/ApplyVelocityMsg.h"
#include <string>

using namespace std;

extern Coordinator gCoordinator;
extern MessageBus msgBus;

void ControllerSystem::Init() {
	velocity = 10;
}

void ControllerSystem::Update() {

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

void ControllerSystem::changeState(Entity a_entity, State a_state) {
	auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(a_entity);
	int playerId = playerIdComponent.playerId;
	if (playerId == 1) {
		player1Fsm.changeState(a_state);
	}
	else if (playerId == 2) {
		player2Fsm.changeState(a_state);
	}
}

void ControllerSystem::notifyAnimationSystem(string newState, string currentState, Entity a_entity) {
	ChangeAnimationMsg changeAnimMsg = ChangeAnimationMsg(newState, currentState, a_entity);
	msgBus.postMessage(&changeAnimMsg);
}

void ControllerSystem::notifyPhysicsSystem(Entity a_entity) {
	ApplyVelocityMsg applyVelMsg = ApplyVelocityMsg(a_entity);
	msgBus.postMessage(&applyVelMsg);
}

void ControllerSystem::handleHorizontalMove(State stateToChangeTo, PlayerFSM stateMachine, Entity playerToMove, float xDirection) {
	string currentState = stateMachine.getCurrentStateAsString();
	string newStateAsString = stateMachine.getStateAsString(stateToChangeTo);

	if (stateMachine.changeState(stateToChangeTo)) {
		Vec3 directionVector = Vec3(xDirection, 0, 0);
		moveEntity(playerToMove, directionVector * velocity);
		notifyAnimationSystem(newStateAsString, currentState, playerToMove);
	}
}

void ControllerSystem::handleVerticalMove(Entity a_entity, PlayerFSM stateMachine) {
	if (stateMachine.changeState(State::JUMPING)) {
		string currentState = stateMachine.getCurrentStateAsString();
		string stateToChangeTo = "Jumping";

		notifyAnimationSystem(stateToChangeTo, currentState, a_entity);
		notifyPhysicsSystem(a_entity);
	}
}

void ControllerSystem::stopMovement(Entity playerEntity, PlayerFSM stateMachine){
	if (stateMachine.changeState(State::IDLE)) {
		string animationToChangeTo = "Idle";
		string currentState = stateMachine.getCurrentStateAsString();
		notifyAnimationSystem(animationToChangeTo, currentState, playerEntity);
	}
}

void ControllerSystem::startFightAction(State a_move, PlayerFSM stateMachine) {
	string currentState = stateMachine.getCurrentStateAsString();
	string newState = stateMachine.getStateAsString(a_move);
	if (player1Fsm.changeState(a_move)) {
		notifyAnimationSystem(newState, currentState, firstPlayerEnt);
	}
}

void ControllerSystem::onKeyDown(int keyPress)
{
	setPlayerEntityIds();
	switch (keyPress)
	{
	//------------------------PLAYER 1 MOVEMENTS------------------------------
	case 87://W
		handleVerticalMove(firstPlayerEnt, player1Fsm);
		break;
	case 83://S
		break;
		//create message and send to animation to start crouch anim
	case 65://A
	{
		State stateToChangeTo = State::WALKING_BCK;
		handleHorizontalMove(stateToChangeTo, player1Fsm, firstPlayerEnt, -1);
		break;
	}
	case 68://D
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player1Fsm, firstPlayerEnt, 1);
		break;
	}
	case 84: //T Light punch
	{
		State stateToChangeTo = State::LIGHT_PUNCH;
		startFightAction(stateToChangeTo, player1Fsm);
		break;
	}
	case 89: //Y Heavy punch
	{
		State stateToChangeTo = State::HEAVY_PUNCH;
		startFightAction(stateToChangeTo, player1Fsm);
		break;
	}
	case 71: //G Light kick
	{
		State stateToChangeTo = State::LIGHT_KICK;
		startFightAction(stateToChangeTo, player1Fsm);
		break;
	}
	case 72: //H Heavy kick
	{
		State stateToChangeTo = State::HEAVY_KICK;
		startFightAction(stateToChangeTo, player1Fsm);
		break;
	}
//------------------------PLAYER 2 MOVEMENTS------------------------------
	case 38: //Arrow-UP
	{
		handleVerticalMove(secondPlayerEnt, player2Fsm);
		break;
	}
	case 40: //Arrow-DOWN
	{
		break;
	}
	case 37: //Arrow-LEFT
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player2Fsm, secondPlayerEnt, -1);
		break;
	}
	case 39: //Arrow-RIGHT
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player2Fsm, secondPlayerEnt, 1);
		break;
	}
	case 79: //O Light punch
	{
		State stateToChangeTo = State::LIGHT_PUNCH;
		startFightAction(stateToChangeTo, player2Fsm);
		break;
	}
	case 73: //I Heavy punch
	{
		State stateToChangeTo = State::HEAVY_PUNCH;
		startFightAction(stateToChangeTo, player2Fsm);
		break;
	}
	case 76: //L light kick
	{
		State stateToChangeTo = State::LIGHT_KICK;
		startFightAction(stateToChangeTo, player2Fsm);
		break;
	}
	case 75: //K heavy kick
	{
		State stateToChangeTo = State::HEAVY_KICK;
		startFightAction(stateToChangeTo, player2Fsm);
		break;
	}
	default:
	{
		break;
	}
	}
}

void ControllerSystem::onKeyUp(int keyPress)
{
	switch (keyPress)
	{
	//------------------------PLAYER 1 MOVEMENTS------------------------------
	case 87://W
	{
		break;
	}
	case 83://S
	{
		break;
	}
	case 65://A
	{
		stopMovement(firstPlayerEnt, player1Fsm);
		break;
	}
	case 68://D
	{
		stopMovement(firstPlayerEnt, player1Fsm);
		break;
	}
	//------------------------PLAYER 2 MOVEMENTS------------------------------
	case 37: //Arrow-LEFT
	{
		stopMovement(secondPlayerEnt, player2Fsm);
		break;
	}
	case 39: //Arrow-RIGHT
	{
		stopMovement(secondPlayerEnt, player2Fsm);
		break;
	}
	default:
		break;
	}
}

void ControllerSystem::handleMessage(Message* msg)
{
	MessageId idToCheck = MessageId::CHANGE_STATE;
	if (msg->checkId(&idToCheck)) {
		ChangeStateMsg* changeStateMsg = (ChangeStateMsg*)msg;

		Entity entity = changeStateMsg->entity;
		State state = changeStateMsg->state;

		changeState(entity, state);
	}
}
