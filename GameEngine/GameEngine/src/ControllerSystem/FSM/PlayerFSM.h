#pragma once
#include "FSM.h"
#include <string>

using namespace std;

class PlayerFSM : public FSM
{
private:
	int stateChart[8][8] = {
        {0,1,1,1,1,1,1,1}, //idle
        {1,1,1,1,1,1,1,1}, //Walking_fwd
        {1,1,1,1,1,1,1,1}, //Walking_bck
        {1,0,0,0,0,0,0,0}, //Jumping
        {1,0,0,0,0,0,0,0}, //Light_punch
        {1,0,0,0,0,0,0,0}, //Heavy_punch
        {1,0,0,0,0,0,0,0}, //Light_kick
        {1,0,0,0,0,0,0,0}  //Heavy_kick
    }; 

    string states[8] = { "Idle", "Walking_fwd", "Walking_bck", "Jumping", "Light_punch", "Heavy_punch", "Light_kick", "Heavy_kick" };

public:
	// Inherited via FSM
	virtual bool changeState(State state) override;
    string getStateAsString(State state);
    string getCurrentStateAsString();
};

