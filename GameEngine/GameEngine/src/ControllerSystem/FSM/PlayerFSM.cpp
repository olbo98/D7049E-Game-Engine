#include "PlayerFSM.h"

string PlayerFSM::getCurrentStateAsString() {
    return states[(char)getCurrentState()];
}

string PlayerFSM::getStateAsString(State state) {
    return states[(char)state];
}

bool PlayerFSM::changeState(State state)
{
    if (stateChart[(char)currentState][(char)state]) {
        currentState = state;
        return true;
    }
    return false;
}
