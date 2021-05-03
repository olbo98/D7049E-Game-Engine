#pragma once
/*!
* Messages that are sent between systems via the message bus. Should currently only be used by systems and the message bus.
*/
enum class Message {
	NULL_MESSAGE,
	OPEN_MENU, 
	CLOSE_MENU
};