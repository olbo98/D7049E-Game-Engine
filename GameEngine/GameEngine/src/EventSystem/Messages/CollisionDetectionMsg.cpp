#include "CollisionDetectionMsg.h"

CollisionDetectionMsg::CollisionDetectionMsg(Entity first, Entity second) {
	id = MessageId::COLLISION_DETECTION;
	firstEntity = first;
	secondEntity = second;
}
