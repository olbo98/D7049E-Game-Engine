#pragma once
#include "FSM.h"

using namespace std;

class Player1FSM : public FSM
{
private:
	int stateChart[8][8] = {
        {0,1,1,1,1,1,1,1}, //idle
        {1,0,1,1,1,1,1,1}, //Walking_fwd
        {1,1,0,1,1,1,1,1}, //Walking_bck
        {1,0,0,0,0,0,0,0}, //Jumping
        {1,0,0,0,0,0,0,0}, //Light_punch
        {1,0,0,0,0,0,0,0}, //Heavy_punch
        {1,0,0,0,0,0,0,0}, //Light_kick
        {1,0,0,0,0,0,0,0}  //Heavy_kick
    }; 

public:
	// Inherited via FSM
	virtual bool changeState(State state) override;
};

