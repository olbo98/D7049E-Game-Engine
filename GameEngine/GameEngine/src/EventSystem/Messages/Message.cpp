#include "Message.h"

bool Message::checkId(MessageId* idToCheck) {
	if (*idToCheck == id) {
		return true;
	}
	return false;
}