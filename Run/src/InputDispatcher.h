#pragma once
#include <SFML/Graphics.hpp>
#include "InputReceiver.h"

class InputDispatcher
{
private:
    sf::RenderWindow *m_window;
    std::vector<InputReceiver *> m_inputReceivers;

public:
    InputDispatcher(sf::RenderWindow *window);
    void dispatchInputEvents();
    void registerNewInputReceiver(InputReceiver *ir);
};