#include "CameraUpdate.h"

#include "PlayerUpdate.h"
#include "LevelUpdate.h"

sf::FloatRect *CameraUpdate::getPositionPointer()
{
    return &m_position;
}

void CameraUpdate::assemble(std::shared_ptr<LevelUpdate> levelUpdate,
                            std::shared_ptr<PlayerUpdate> playerUpdate)
{
    m_playerPosition = playerUpdate->getPositionPointer();
}

InputReceiver *CameraUpdate::gerInputReceiver()
{
    m_inputrecevicer = new InputReceiver;
    m_receiversInput = true;
    return m_inputrecevicer;
}

void CameraUpdate::handleInput()
{
    m_position.size.x = 1.0f;

    for (std::optional event : m_inputrecevicer->getEvents())
    {
        if(auto *mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>()){
             if (mouseWheel->wheel == sf::Mouse::Wheel::Vertical)
            {
                m_position.size.x *= (mouseWheel->delta > 0) ? 0.95f : 1.05f;
            }
        }
        m_inputrecevicer->clearEvents();
    }
}

void CameraUpdate::update(float fps){
    if(m_receiversInput){
        handleInput();
        m_position.position.x = m_playerPosition->position.x;
        m_position.position.y = m_playerPosition->position.y;
    }else{
        m_position.position.x = m_playerPosition->position.x;
        m_position.position.y = m_playerPosition->position.y;
        m_position.size.x = 1;
    }
}
CameraUpdate::~CameraUpdate()
{
    delete m_inputrecevicer;
}