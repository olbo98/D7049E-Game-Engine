#include "Player2Controller.h"

extern Coordinator gCoordinator;
extern MessageBus msgBus;

Player2Controller::Player2Controller() {
	velocity = 10;
	player2Fsm = new PlayerFSM();
}

void Player2Controller::Init() {

}

void Player2Controller::Update(const Ogre::FrameEvent& fe) {

}

void Player2Controller::setActiveEntity(Entity a_entity) {
	activeEntity = a_entity;
}


void Player2Controller::setPlayerEntityIds() {
	//auto& lastPlayerIdComponent = gCoordinator.getComponent<PlayerId>(activeEntity);
	//for (auto const& entity : m_entities) {
	//	auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(entity);

	//	if (lastPlayerIdComponent.playerId != playerIdComponent.playerId) {
	//		std::cout << "Change active p" << std::endl;
	//		if (playerIdComponent.playerId == 1) {
	//			//firstPlayerEnt = entity;
	//			activeEntity = entity;
	//		}

	//		if (playerIdComponent.playerId == 2) {
	//			activeEntity == entity;
	//			//secondPlayerEnt = entity;
	//		}
	//	}
	//}
	for (auto const& entity : m_entities) {
		auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(entity);
		if (playerIdComponent.playerId == 2) {
			activeEntity = entity;
		}
	}
}

void Player2Controller::moveEntity(Entity entityToMove, Vec3 a_velocity) {
	auto& transformComponent = gCoordinator.getComponent<Transform>(entityToMove);
	Vec3 position = transformComponent.node->getPosition();
	position += a_velocity;
	transformComponent.node->setPosition(position.toOgre());
}

void Player2Controller::changeState(Entity a_entity, State a_state) {
	auto& playerIdComponent = gCoordinator.getComponent<PlayerId>(a_entity);
	int playerId = playerIdComponent.playerId;

	player2Fsm->changeState(a_state);
}

void Player2Controller::notifyAnimationSystem(string newState, string currentState, Entity a_entity) {
	ChangeAnimationMsg* changeAnimMsg = new ChangeAnimationMsg(newState, currentState, a_entity);
	msgBus.postMessage(changeAnimMsg);
}

void Player2Controller::notifyPhysicsSystem(Entity a_entity) {
	ApplyVelocityMsg applyVelMsg = ApplyVelocityMsg(a_entity);
	msgBus.postMessage(&applyVelMsg);
}

void Player2Controller::handleHorizontalMove(State stateToChangeTo, PlayerFSM* stateMachine, Entity playerToMove, float xDirection) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newStateAsString = stateMachine->getStateAsString(stateToChangeTo);

	if (stateMachine->changeState(stateToChangeTo)) {
		Vec3 directionVector = Vec3(xDirection, 0, 0);
		moveEntity(playerToMove, directionVector * velocity);
		notifyAnimationSystem(newStateAsString, currentState, playerToMove);
	}
}

void Player2Controller::handleVerticalMove(Entity a_entity, PlayerFSM* stateMachine) {
	if (stateMachine->changeState(State::JUMPING)) {
		string currentState = stateMachine->getCurrentStateAsString();
		string stateToChangeTo = "Jumping";

		notifyAnimationSystem(stateToChangeTo, currentState, a_entity);
		notifyPhysicsSystem(a_entity);
	}
}

void Player2Controller::stopMovement(Entity playerEntity, PlayerFSM* stateMachine) {
	if (stateMachine->changeState(State::IDLE)) {
		string animationToChangeTo = "Idle";
		string currentState = stateMachine->getCurrentStateAsString();
		notifyAnimationSystem(animationToChangeTo, currentState, playerEntity);
	}
}

void Player2Controller::startFightAction(State a_move, PlayerFSM* stateMachine, Entity playerEntity) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newState = stateMachine->getStateAsString(a_move);

	if (stateMachine->changeState(a_move)) {
		notifyAnimationSystem(newState, currentState, playerEntity);
	}
}

void Player2Controller::onKeyDown(int keyPress)
{
	setPlayerEntityIds();

	//------------------------PLAYER 2 MOVEMENTS------------------------------
	switch (keyPress) {
	case 1073741906: //Arrow-UP
	{
		handleVerticalMove(activeEntity, player2Fsm);
		break;
	}
	case 1073741905: //Arrow-DOWN
	{
		break;
	}
	case 1073741904: //Arrow-LEFT
	{
		State stateToChangeTo = State::WALKING_BCK;
		handleHorizontalMove(stateToChangeTo, player2Fsm, activeEntity, -1);
		break;
	}
	case 1073741903: //Arrow-RIGHT
	{
		State stateToChangeTo = State::WALKING_FWD;
		handleHorizontalMove(stateToChangeTo, player2Fsm, activeEntity, 1);
		break;
	}
	case 111: //O Light punch
	{
		State stateToChangeTo = State::LIGHT_PUNCH;
		startFightAction(stateToChangeTo, player2Fsm, activeEntity);
		break;
	}
	case 105: //I Heavy punch
	{
		State stateToChangeTo = State::HEAVY_PUNCH;
		startFightAction(stateToChangeTo, player2Fsm, activeEntity);
		break;
	}
	case 108: //L light kick
	{
		State stateToChangeTo = State::LIGHT_KICK;
		startFightAction(stateToChangeTo, player2Fsm, activeEntity);
		break;
	}
	case 107: //K heavy kick
	{
		State stateToChangeTo = State::HEAVY_KICK;
		startFightAction(stateToChangeTo, player2Fsm, activeEntity);
		break;
	}
	default:
	{
		break;
	}
	}
}

void Player2Controller::onKeyUp(int keyPress)
{
	//------------------------PLAYER 2 MOVEMENTS------------------------------
	switch (keyPress) {
		case 1073741906: //Arrow-UP
		{
			//player2Fsm->changeState(State::IDLE);
			break;
		}
		case 1073741905: //Arrow-DOWN
		{
			//player2Fsm->changeState(State::IDLE);
			break;
		}
		case 1073741904: //Arrow-LEFT
		{
			stopMovement(activeEntity, player2Fsm);
			break;
		}
		case 1073741903: //Arrow-RIGHT
		{
			stopMovement(activeEntity, player2Fsm);
			break;
		}
		default:
			break;
	}
}

void Player2Controller::handleMessage(Message* msg)
{
	MessageId idToCheck = MessageId::CHANGE_STATE;
	if (msg->checkId(&idToCheck)) {
		ChangeStateMsg* changeStateMsg = (ChangeStateMsg*)msg;

		Entity entity = changeStateMsg->entity;
		State state = changeStateMsg->state;

		auto& playerComp = gCoordinator.getComponent<PlayerId>(entity);
		if (playerComp.playerId == 2) {
			changeState(entity, state);
		}
	}
}