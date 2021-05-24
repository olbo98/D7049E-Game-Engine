#include "InputSystem.h"
#include <Windows.h>
#include <iostream>

extern MessageBus msgBus;

InputSystem::InputSystem() 
{
   
}

InputSystem::~InputSystem() 
{

}

void InputSystem::addListeners(InputListener* listener)
{
    m_set_listeners.insert(listener);
}

void InputSystem::removeListeners(InputListener* listener)
{
    m_set_listeners.erase(listener);
}

/* Notifies state changes to the listeners */
void InputSystem::Update(const Ogre::FrameEvent& fe)
{
	if (GetKeyboardState(key_states))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (GetAsyncKeyState(key_states[i]) & 0x8000)
			{
				std::cout << "A KEY IS DOWN" << std::endl;
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				while (it != m_set_listeners.end())
				{
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else // KEY IS UP
			{
				//std::cout << "A KEY IS UP" << std::endl;
				if (key_states[i] != old_key_states[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		memcpy(old_key_states, key_states, sizeof(unsigned char) * 256);
	}
}



InputSystem* InputSystem::getInstance()
{
    static InputSystem system;
    return &system;
}

void InputSystem::handleMessage(Message* msg)
{
    
}
