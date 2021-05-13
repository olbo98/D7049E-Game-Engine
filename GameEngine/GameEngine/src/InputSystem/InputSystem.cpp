#include "InputSystem.h"
#include <Windows.h>
#include <iostream>

InputSystem::InputSystem() 
{
   
}

InputSystem::~InputSystem() 
{

}

void InputSystem::addListeners(InputListener* listener)
{
    //insterting the listeners into the map_container
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

void InputSystem::setMsgBus(MessageBus* mb)
{
    msgBus = mb;
}

/* Notifies state changes to the listeners */
void InputSystem::update()
{
    
    for (int i = 0; i < 256; i++)
    {
        key_states[i] = GetAsyncKeyState(i);
            
        //KEY is down
        if (key_states[i] > 0)
        {
             //iterating through the container of listeners
            std::map<InputListener*, InputListener*>::iterator it = map_listeners.begin();
            while (it != map_listeners.end())
            {
                it->first->onKeyDown(i, msgBus);
                ++it;
            }
               
        }
        //KEY is up 
        else if(key_states[i] == 0)
        {
            //KEY release event
            if (key_states[i] != old_key_states[i]) 
            {
                std::map<InputListener*, InputListener*>::iterator it = map_listeners.begin();
                while (it != map_listeners.end())
                {
                    it->first->onKeyUp(i, msgBus);
                    ++it;
                }

                    
            }
        }
    }
    // store current key states to old key states buffer
    ::memcpy(old_key_states, key_states, sizeof(unsigned char) * 256);

}


InputSystem* InputSystem::getInstance()
{
    static InputSystem system;
    return &system;
}

void InputSystem::handleMessage(Message* msg)
{
    if (*msg == Message::CLOSE_MENU) {
        std::cout << "Received close menu message" << std::endl;
    }
}
