#include "PlatformUpdate.h"
#include "PlayerUpdate.h"

sf::FloatRect *PlatformUpdate::getPositionPointer()
{
    return &m_position;
}

void PlatformUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate)
{
    m_playerPosition = playerUpdate->getPositionPointer();
    m_playerIsGrounded = playerUpdate->getGroundedPointer();
}

void PlatformUpdate::update(float fps)
{
    if (m_position.findIntersection(*m_playerPosition))
    {
        sf::Vector2f playerFeet(
            m_playerPosition->position.x + m_playerPosition->size.x / 2,
            m_playerPosition->position.y + m_playerPosition->size.y);
    }
}