#include "FSM.h"

State FSM::getCurrentState() {
	return currentState;
};

void FSM::setCurrentState(State newState) {
	currentState = newState;
}