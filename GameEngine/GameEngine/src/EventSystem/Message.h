#pragma once
enum class Id {
	NULL_MESSAGE,
	OPEN_MENU,
	CLOSE_MENU,
	INPUT
};

/*!
* Messages that are sent between systems via the message bus. Should currently only be used by systems and the message bus.
*/
class Message {
protected:
	Id id;
public:
	bool checkId(Id* idToCheck);
};
