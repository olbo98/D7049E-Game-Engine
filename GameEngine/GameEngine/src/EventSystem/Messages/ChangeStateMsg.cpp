#include "ChangeStateMsg.h"

ChangeStateMsg::ChangeStateMsg(State a_state, Entity a_entity) {
	id = MessageId::CHANGE_STATE;
	state = a_state;
	entity = a_entity;
}