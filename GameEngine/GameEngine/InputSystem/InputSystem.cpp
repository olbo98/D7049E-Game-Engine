#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem() 
{
   
}

InputSystem::~InputSystem() 
{

}

void InputSystem::addListeners(InputListener* listener)
{
    map_listeners.insert(std::make_pair<InputListener*, InputListener*>
        (std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void InputSystem::removeListeners(InputListener* listener)
{
    std::map<InputListener*, InputListener*>::iterator i = map_listeners.find(listener); //iterates the container and finds the listener

    if (i != map_listeners.end())
    {
        map_listeners.erase(i);
    }
}

/* Notifies state changes to the listeners */
void InputSystem::update()
{
    if (::GetKeyboardState(key_states)) //"GetKeyboardState" retrieves the states of each key in the keyboard
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            //KEY is down
            if (key_states[i] & 0x80) //bitmasks the higher order of the value and will be evaluated 
            {
                std::map<InputListener*, InputListener*>::iterator it = map_listeners.begin();
                while (it != map_listeners.end())
                {
                    it->second->onKeyDown(i);
                    ++it;
                }

            }
            //KEY is up 
            else
            {
                //KEY release event
                if (key_states[i] != old_key_states[i]) 
                {
                    std::map<InputListener*, InputListener*>::iterator it = map_listeners.begin();
                    while (it != map_listeners.end())
                    {
                        it->second->onKeyUp(i);
                        ++it;
                    }
                }
            }
        }
        // store current keys state to old keys state buffer
        ::memcpy(old_key_states, key_states, sizeof(unsigned char) * 256);
    }
}

/*
InputSystem* InputSystem::getInstance()
{
    if(inputSystem == nullptr)
    {
        inputSystem = new InputSystem();
    }
    return inputSystem;
}*/

InputSystem* InputSystem::getInstance()
{
    static InputSystem system;
    return &system;
}
