#include "ApplyVelocityMsg.h"

ApplyVelocityMsg::ApplyVelocityMsg(Entity a_entity) {
	id = MessageId::APPLY_VELOCITY;
	entity = a_entity;
}