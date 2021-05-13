#pragma once
enum class MessageId : char {
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
	MessageId id;
public:
	bool checkId(MessageId* idToCheck);
};