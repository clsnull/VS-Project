#include "FireballUpdate.h"
#include <random>
#include "SoundEngine.h"
#include "PlayerUpdate.h"

FireballUpdate::FireballUpdate(bool* pausedPointer)
{
    m_gameIsPaused = pausedPointer;
    m_pauseDurationTarget = getRandomNumber(m_minPause, m_maxPause);
}

bool* FireballUpdate::getFacingRightPointer()
{
    return &m_leftToRight;
}

FloatRect* FireballUpdate::getPositionPointer()
{
    return &m_position;
}

void FireballUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate)
{
    m_playerPosition = playerUpdate->getPositionPointer();
    m_position.position.y = getRandomNumber(
        m_playerPosition->position.y - m_maxSpawnDistanceFromPlayer,
        m_playerPosition->position.y + m_maxSpawnDistanceFromPlayer);
    m_position.position.x = m_playerPosition->position.x - getRandomNumber(200, 400);
    m_position.size.x = 10;
    m_position.size.y = 10;
}

int FireballUpdate::getRandomNumber(int minHeight, int maxHeight) {
    // Seed the random number generator with current time
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define a uniform distribution for the desired range
    std::uniform_int_distribution<int> distribution(minHeight, maxHeight);
    
    // Generate a random height within the specified range
    int randomHeight = distribution(gen);
    
    return randomHeight;
}

void FireballUpdate::update(float fps) 
{
    if (!*m_gameIsPaused) 
    {
        if (!m_movementPaused) 
        {
            if (m_leftToRight) 
            {
                m_position.position.x += m_speed * fps;
                if (m_position.position.x - m_playerPosition->position.x > m_range) 
                {
                    m_movementPaused = true;
                    m_pauseClock.restart();
                    m_leftToRight = !m_leftToRight;
                    m_position.position.x = getRandomNumber(
                        m_playerPosition->position.x - m_maxSpawnDistanceFromPlayer,
                        m_playerPosition->position.x + m_maxSpawnDistanceFromPlayer
                    );
                    m_pauseDurationTarget = getRandomNumber(m_minPause, m_maxPause);
                }
            } 
            else 
            {
                m_position.position.x -= m_speed * fps;
                if (m_playerPosition->position.x - m_position.position.x > m_range) 
                {
                    m_movementPaused = true;
                    m_pauseClock.restart();
                    m_leftToRight = !m_leftToRight;
                    m_position.position.y = getRandomNumber(
                        m_playerPosition->position.y - m_maxSpawnDistanceFromPlayer,
                        m_playerPosition->position.y + m_maxSpawnDistanceFromPlayer
                    );
                    m_pauseDurationTarget = getRandomNumber(m_minPause, m_maxPause);
                }
            }
            // Has it hit the player
            if (m_playerPosition->contains(m_position.position)) 
            {
                // Knock the player down
                m_playerPosition->position.x += m_playerPosition->size.y * 2;
            }
        } 
        else 
        {
            if (m_pauseClock.getElapsedTime().asSeconds() > m_pauseDurationTarget) 
            {
                m_movementPaused = false;
                SoundEngine::playFireballLaunch(
                    m_playerPosition->position,
                    m_position.position
                );
            }
        }
    }
}
