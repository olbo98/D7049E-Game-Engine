#pragma once

enum class State : char {
	IDLE,
	WALKING_FWD,
	WALKING_BCK,
	JUMPING,
	LIGHT_PUNCH,
	HEAVY_PUNCH,
	LIGHT_KICK,
	HEAVY_KICK
};