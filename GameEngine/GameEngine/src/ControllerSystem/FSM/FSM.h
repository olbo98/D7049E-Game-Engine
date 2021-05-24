#pragma once
#include <string>
#include "States/State.h"

using namespace std;

class FSM
{
public:
	//! Returns the current state of the FSM
	State getCurrentState();
	void setCurrentState(State newState);
	//! Change the state of the FSM
	/*!
	* Changes the current state of the FSM to the new state
	* 
	* \param state the state to change to
	* \return True if the FSM was able to change state, otherwise False
	*/
	virtual bool changeState(State state) = 0;
protected:
	State currentState;
};

