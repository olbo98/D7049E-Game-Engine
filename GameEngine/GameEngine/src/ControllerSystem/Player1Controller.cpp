#include "Player1Controller.h"

extern Coordinator gCoordinator;
extern MessageBus msgBus;

Player1Controller::Player1Controller() {
	velocity = 10;
	player1Fsm = new PlayerFSM();
	player2Fsm = new PlayerFSM();
}

void Player1Controller::Init() {

}

void Player1Controller::Update(const Ogre::FrameEvent& fe) {

}

void Player1Controller::setActiveEntity(Entity a_entity) {
	activeEntity = a_entity;
}


void Player1Controller::setPlayerEntityIds() {
	for (auto const& entity : m_entities) {
		auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(entity);
		if (playerIdComponent.playerId == 1) {
			activeEntity == entity;
		}
	}
}

void Player1Controller::moveEntity(Entity entityToMove, Vec3 a_velocity) {
	auto& transformComponent = gCoordinator.getComponent<Transform>(entityToMove);
	Vec3 position = transformComponent.node->getPosition();
	position += a_velocity;
	transformComponent.node->setPosition(position.toOgre());
}

void Player1Controller::changeState(Entity a_entity, State a_state) {
	auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(a_entity);
	int playerId = playerIdComponent.playerId;

	if (playerId == 1) {
		player1Fsm->changeState(a_state);
	}
	else if (playerId == 2) {
		player2Fsm->changeState(a_state);
	}
}

void Player1Controller::notifyAnimationSystem(string newState, string currentState, Entity a_entity) {
	ChangeAnimationMsg* changeAnimMsg = new ChangeAnimationMsg(newState, currentState, a_entity);
	msgBus.postMessage(changeAnimMsg);
}

void Player1Controller::notifyPhysicsSystem(Entity a_entity) {
	ApplyVelocityMsg applyVelMsg = ApplyVelocityMsg(a_entity);
	msgBus.postMessage(&applyVelMsg);
}

void Player1Controller::handleHorizontalMove(State stateToChangeTo, PlayerFSM* stateMachine, Entity playerToMove, float xDirection) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newStateAsString = stateMachine->getStateAsString(stateToChangeTo);

	if (stateMachine->changeState(stateToChangeTo)) {
		Vec3 directionVector = Vec3(xDirection, 0, 0);
		moveEntity(playerToMove, directionVector * velocity);
		notifyAnimationSystem(newStateAsString, currentState, playerToMove);
	}
}

void Player1Controller::handleVerticalMove(Entity a_entity, PlayerFSM* stateMachine) {
	if (stateMachine->changeState(State::JUMPING)) {
		string currentState = stateMachine->getCurrentStateAsString();
		string stateToChangeTo = "Jumping";

		notifyAnimationSystem(stateToChangeTo, currentState, a_entity);
		notifyPhysicsSystem(a_entity);
	}
}

void Player1Controller::stopMovement(Entity playerEntity, PlayerFSM* stateMachine) {
	if (stateMachine->changeState(State::IDLE)) {
		string animationToChangeTo = "Idle";
		string currentState = stateMachine->getCurrentStateAsString();
		notifyAnimationSystem(animationToChangeTo, currentState, playerEntity);
	}
}

void Player1Controller::startFightAction(State a_move, PlayerFSM* stateMachine, Entity playerEntity) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newState = stateMachine->getStateAsString(a_move);

	if (stateMachine->changeState(a_move)) {
		notifyAnimationSystem(newState, currentState, playerEntity);
	}
}

void Player1Controller::onKeyDown(int keyPress)
{
	setPlayerEntityIds();

	switch (keyPress)
	{
		//------------------------PLAYER 1 MOVEMENTS------------------------------
	case 119://W
		handleVerticalMove(activeEntity, player1Fsm);
		break;
	case 115://S
		break;
		//create message and send to animation to start crouch anim
	case 97://A
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player1Fsm, activeEntity, -1);
		break;
	}
	case 100://D
	{
		State stateToChangeTo = State::WALKING_BCK;
		handleHorizontalMove(stateToChangeTo, player1Fsm, activeEntity, 1);
		break;
	}
	case 116: //T Light punch
	{
		State stateToChangeTo = State::LIGHT_PUNCH;
		startFightAction(stateToChangeTo, player1Fsm, activeEntity);
		break;
	}
	case 121: //Y Heavy punch
	{
		State stateToChangeTo = State::HEAVY_PUNCH;
		startFightAction(stateToChangeTo, player1Fsm, activeEntity);
		break;
	}
	case 103: //G Light kick
	{
		State stateToChangeTo = State::LIGHT_KICK;
		startFightAction(stateToChangeTo, player1Fsm, activeEntity);
		break;
	}
	case 104: //H Heavy kick
	{
		State stateToChangeTo = State::HEAVY_KICK;
		startFightAction(stateToChangeTo, player1Fsm, activeEntity);
		break;
	}
	}
}

void Player1Controller::onKeyUp(int keyPress)
{
	switch (keyPress)
	{
		//------------------------PLAYER 1 MOVEMENTS------------------------------
	case 119://W
	{
		//player1Fsm->changeState(State::IDLE);
		break;
	}
	case 115://S
	{
		//player1Fsm->changeState(State::IDLE);
		break;
	}
	case 97://A
	{
		stopMovement(activeEntity, player1Fsm);
		break;
	}
	case 100://D
	{
		stopMovement(activeEntity, player1Fsm);
		break;
	}
	}
	//case 116: //T
	//{
	//}
	//case 121: //Y Heavy punch
	//{
	//}
	//case 103: //G Light kick
	//{
	//}
	//case 104: //H Heavy kick
	//{
	//}
}

void Player1Controller::handleMessage(Message* msg)
{
	MessageId idToCheck = MessageId::CHANGE_STATE;
	if (msg->checkId(&idToCheck)) {
		ChangeStateMsg* changeStateMsg = (ChangeStateMsg*)msg;

		Entity entity = changeStateMsg->entity;
		State state = changeStateMsg->state;

		auto& playerComp = gCoordinator.getComponent<PlayerId>(entity);
		if (playerComp.playerId == 1) {
			changeState(entity, state);
		}
	}
}