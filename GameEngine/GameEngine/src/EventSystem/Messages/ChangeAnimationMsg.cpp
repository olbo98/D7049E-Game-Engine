#include "ChangeAnimationMsg.h"

ChangeAnimationMsg::ChangeAnimationMsg(string a_animation, string currentAnim, Entity a_entity) {
	id = MessageId::CHANGE_ANIMATION;
	newAnimationState = a_animation;
	currentAnimationState = currentAnim;
	entity = a_entity;
}