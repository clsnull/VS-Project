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

        sf::Vector2f playerRight(
            m_playerPosition->position.x + m_playerPosition->size.x,
            m_playerPosition->position.y + m_playerPosition->size.y / 2);

        sf::Vector2f playerLeft(
            m_playerPosition->position.x,
            m_playerPosition->size.y / 2);

        sf::Vector2f playerHead(
            m_playerPosition->position.x + m_playerPosition->size.x / 2,
            m_playerPosition->size.y);

        if (m_position.contains(playerFeet))
        {
            if (playerFeet.y > m_position.position.x)
            {
                m_playerPosition->position.x = m_position.position.x - m_playerPosition->size.y;
                *m_playerIsGrounded = true;
            }
        }
        else if (m_position.contains(playerRight))
        {
            m_playerPosition->position.x = m_position.position.x - m_playerPosition->size.x;
        }
        else if (m_position.contains(playerLeft))
        {
            m_playerPosition->position.x = m_position.position.x + m_playerPosition->size.x;
        }
        else if (m_position.contains(playerHead))
        {
            m_playerPosition->position.y = m_position.position.x + m_position.size.y;
        }
    }
}