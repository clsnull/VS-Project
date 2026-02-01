#include "InputReceiver.h"

void InputReceiver::addEvent(std::optional<sf::Event> event)
{
    m_evens.push_back(event);
}

std::vector<std::optional<sf::Event>> &InputReceiver::getEvents()
{
    return m_evens;
}

void InputReceiver::clearEvents(){
    m_evens.clear();
}