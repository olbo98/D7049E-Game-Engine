#pragma once
#include "../EntityComponentSystem/System.h"
#include "../InputSystem/InputListener.h"
#include "FSM/PlayerFSM.h"
#include "../Utils/Utils.h"

class ControllerSystem : public InputListener, public System
{
public:
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress) override; //TODO Remove the message bus parameter to the onKeyDown/Up functions
	virtual void onKeyUp(int keyPress) override;

	// Inherited via System
	virtual void handleMessage(Message* msg) override;

	virtual void Update(const Ogre::FrameEvent& fe) override;

	ControllerSystem();

private:
	PlayerFSM player1Fsm;
	PlayerFSM player2Fsm;
	int velocity;
	Entity firstPlayerEnt = 0;
	Entity secondPlayerEnt = 0;

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
	void handleHorizontalMove(State stateToChangeTo, PlayerFSM stateMachine, Entity playerToMove, float xDirection);
};

