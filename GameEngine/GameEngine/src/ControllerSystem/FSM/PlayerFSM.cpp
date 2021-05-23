#include "PlayerFSM.h"
#include <iostream>

string PlayerFSM::getCurrentStateAsString() {
    return states[(int)getCurrentState()];
}

string PlayerFSM::getStateAsString(State state) {
    return states[(int)state];
}

bool PlayerFSM::changeState(State state)
{
    if (stateChart[(int)currentState][(int)state]) {
        currentState = state;
        return true;
    }
    else {
        return false;
    }
}
