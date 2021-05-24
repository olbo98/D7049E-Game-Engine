#pragma once
#include "../EntityComponentSystem/System.h"
#include "../InputSystem/InputListener.h"
#include "FSM/PlayerFSM.h"
#include "../Utils/Utils.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/PlayerId.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include "../EventSystem/Messages/ChangeStateMsg.h"
#include "../EventSystem/Messages/ApplyVelocityMsg.h"
#include <string>
#include <iostream>

class Player1Controller : public InputListener, public System
{
public:
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress) override;
	virtual void onKeyUp(int keyPress) override;

	// Inherited via System
	virtual void handleMessage(Message* msg) override;

	void Init();
	void Update();
	void setActiveEntity(Entity a_entity);
	Player1Controller();

private:
	PlayerFSM* player1Fsm;
	PlayerFSM* player2Fsm;
	int velocity;
	Entity activeEntity;
	/*Entity firstPlayerEnt;
	Entity secondPlayerEnt;*/

	//int i = 0;
	//void addPlayerEntity(Entity a_player);


	//! Moves the Entity with a specified velocity
	/*!
	* Moves adds the specified Vec3 to the Vec3 position of the specified entity
	*
	* \param entityToMove the entity that will be moved
	* \param a_velocity velocity
	*/
	void moveEntity(Entity entityToMove, Vec3 a_velocity);

	//! Sends a message to the animation system to start the next animation
	/*!
	* \param newState the new animation state
	* \param currentState current animation state
	* \param a_entity Entity that should change animation state
	*/
	void notifyAnimationSystem(string newState, string currentState, Entity a_entity);

	void notifyPhysicsSystem(Entity a_entity);

	//! Initializes the Entity IDs for the players
	void setPlayerEntityIds();

	//! Handles the horizontal movement
	/*!
	* Changes the state of the state machine, moves the player and notifies the animation system to change animation
	*
	* \param stateToChangeTo The state that the state machine should change to
	* \param stateMachine state machine that should handle the state change
	* \param playerToMove the player Entity that should be moved
	* \param xDirection either -1 or 1. -1 equals left, 1 equals right
	*/
	void handleHorizontalMove(State stateToChangeTo, PlayerFSM* stateMachine, Entity playerToMove, float xDirection);

	void handleVerticalMove(Entity a_entity, PlayerFSM* stateMachine);

	void stopMovement(Entity playerEntity, PlayerFSM* stateMachine);

	void startFightAction(State a_move, PlayerFSM* stateMachine, Entity playerEntity);

	//! Changes the state of an entity
	/*!
	* This should be used when you want to change state of the player but don't care if it's possible in the current state
	*/
	void changeState(Entity a_entity, State a_state);
};

