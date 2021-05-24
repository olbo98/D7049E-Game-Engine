#include "PlayerFSM.h"
#include <iostream>

PlayerFSM::PlayerFSM() {
    currentState = State::IDLE;
}

string PlayerFSM::getCurrentStateAsString() {
    return states[(int)getCurrentState()];
}

string PlayerFSM::getStateAsString(State state) {
    return states[(int)state];
}

State PlayerFSM::getCurrentState() {
    return currentState;
};

void PlayerFSM::setCurrentState(State newState) {
    currentState = newState;
}

bool PlayerFSM::changeState(State state)
{
    int currStateInd = (int)currentState;
    int newStateInd = (int)state;
    
    if (stateChart[currStateInd][newStateInd]) {
        setCurrentState(state);
        return true;
    }
    else {
        return false;
    }
}
