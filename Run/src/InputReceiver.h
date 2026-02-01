#pragma once

#include <SFML/Graphics.hpp>

class InputReceiver
{
private:
    std::vector<std::optional<sf::Event>> m_evens;

public:
    void addEvent(std::optional<sf::Event> event);
    std::vector<std::optional<sf::Event>> &getEvents();
    void clearEvents();
};