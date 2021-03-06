#include "ControllerSystem.h"


extern Coordinator gCoordinator;
extern MessageBus msgBus;

ControllerSystem::ControllerSystem() {
	velocity = 10;
	player1Fsm = new PlayerFSM();
	player2Fsm = new PlayerFSM();
}

void ControllerSystem::Init() {
	
}

void ControllerSystem::setActiveEntity(Entity a_entity) {
	activeEntity = a_entity;
}


void ControllerSystem::setPlayerEntityIds() {
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
		player1Fsm->changeState(a_state);
	}
	else if (playerId == 2) {
		player2Fsm->changeState(a_state);
	}
}

void ControllerSystem::notifyAnimationSystem(string newState, string currentState, Entity a_entity) {
	ChangeAnimationMsg* changeAnimMsg = new ChangeAnimationMsg(newState, currentState, a_entity);
	msgBus.postMessage(changeAnimMsg);
}

void ControllerSystem::notifyPhysicsSystem(Entity a_entity) {
	ApplyVelocityMsg applyVelMsg = ApplyVelocityMsg(a_entity);
	msgBus.postMessage(&applyVelMsg);
}

void ControllerSystem::handleHorizontalMove(State stateToChangeTo, PlayerFSM* stateMachine, Entity playerToMove, float xDirection) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newStateAsString = stateMachine->getStateAsString(stateToChangeTo);

	if (stateMachine->changeState(stateToChangeTo)) {
		Vec3 directionVector = Vec3(xDirection, 0, 0);
		moveEntity(playerToMove, directionVector * velocity);
		notifyAnimationSystem(newStateAsString, currentState, playerToMove);
	}
}

void ControllerSystem::handleVerticalMove(Entity a_entity, PlayerFSM* stateMachine) {
	if (stateMachine->changeState(State::JUMPING)) {
		string currentState = stateMachine->getCurrentStateAsString();
		string stateToChangeTo = "Jumping";

		notifyAnimationSystem(stateToChangeTo, currentState, a_entity);
		notifyPhysicsSystem(a_entity);
	}
}

void ControllerSystem::stopMovement(Entity playerEntity, PlayerFSM* stateMachine){
	if (stateMachine->changeState(State::IDLE)) {
		string animationToChangeTo = "Idle";
		string currentState = stateMachine->getCurrentStateAsString();
		notifyAnimationSystem(animationToChangeTo, currentState, playerEntity);
	}
}

void ControllerSystem::startFightAction(State a_move, PlayerFSM* stateMachine, Entity playerEntity) {
	string currentState = stateMachine->getCurrentStateAsString();
	string newState = stateMachine->getStateAsString(a_move);
	
	if (stateMachine->changeState(a_move)) {
		notifyAnimationSystem(newState, currentState, playerEntity);
	}
}

void ControllerSystem::onKeyDown(int keyPress)
{
	setPlayerEntityIds();

	auto& playerIdComp = gCoordinator.getComponent<PlayerId>(activeEntity);
	int pId = playerIdComp.playerId;

	if (pId == 1) {

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
//------------------------PLAYER 2 MOVEMENTS------------------------------
	if (pId == 2) {
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
}

void ControllerSystem::onKeyUp(int keyPress)
{
	auto& playerIdComp = gCoordinator.getComponent<PlayerId>(activeEntity);
	int pId = playerIdComp.playerId;
	if (pId == 1) {
		switch (keyPress)
		{
			//------------------------PLAYER 1 MOVEMENTS------------------------------
		case 119://W
		{
			player1Fsm->changeState(State::IDLE);
			break;
		}
		case 115://S
		{
			player1Fsm->changeState(State::IDLE);
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
	
	if (pId == 2) {
		//------------------------PLAYER 2 MOVEMENTS------------------------------
		switch (keyPress) {
		case 1073741906: //Arrow-UP
		{
			player2Fsm->changeState(State::IDLE);
			break;
		}
		case 1073741905: //Arrow-DOWN
		{
			player2Fsm->changeState(State::IDLE);
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

void ControllerSystem::Update(const Ogre::FrameEvent& fe) {

}
