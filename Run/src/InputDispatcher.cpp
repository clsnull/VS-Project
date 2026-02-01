#include "InputDispatcher.h"

InputDispatcher::InputDispatcher(sf::RenderWindow *window)
{
    m_window = window;
}

void InputDispatcher::dispatchInputEvents()
{
    while (std::optional<sf::Event> event = m_window->pollEvent())
    {

        if (event->getIf<sf::Event::KeyPressed>())
        {
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
            {
                m_window->close();
            }
        }

        for (const auto &ir : m_inputReceivers)
        {
            ir->addEvent(event);
        }
    }
}

void InputDispatcher::registerNewInputReceiver(InputReceiver *ir)
{
    m_inputReceivers.push_back(ir);
}