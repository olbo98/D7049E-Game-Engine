#include "ChangeStateMsg.h"

ChangeStateMsg::ChangeStateMsg(State a_state) {
	id = MessageId::CHANGE_STATE;
	state = a_state;
}