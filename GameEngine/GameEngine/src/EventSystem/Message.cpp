#include "Message.h"

bool Message::checkId(Id* idToCheck) {
	if (*idToCheck == id) {
		return true;
	}
	return false;
}