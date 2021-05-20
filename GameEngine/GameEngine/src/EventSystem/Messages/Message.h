#pragma once
/*!
* Ids for diffrent messages. When a new message class is created its message id has to be added to this enum class
*/
enum class MessageId : char {
	NULL_MESSAGE,
	OPEN_MENU,
	CLOSE_MENU,
	CHANGE_ANIMATION,
	CHANGE_STATE,
	APPLY_VELOCITY,
	INPUT
};

/*!
* Messages that are sent between systems via the message bus. Should currently only be used by systems and the message bus.
*/
class Message {
protected:
	//! The id of the message. This has to be set in the children classes constructors
	MessageId id; 
public:
	//! Returns true if the passed id is equal to the message id of this class
	/*!
	* \param idToCheck the id to compare
	*/
	bool checkId(MessageId* idToCheck);
};
