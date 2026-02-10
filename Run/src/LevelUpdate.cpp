#include <random>

#include "LevelUpdate.h"

#include "SoundEngine.h"
#include "PlayerUpdate.h"

void LevelUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate)
{
    m_playerPosition = playerUpdate->getPositionPointer();

    SoundEngine::startMusic();
}

void LevelUpdate::connectToCameraTime(float *cameraTime)
{
    m_cameraTime = cameraTime;
}

void LevelUpdate::addPlatformPosition(sf::FloatRect *newPostion)
{
    m_platformPositions.push_back(newPostion);
    m_numberOfPlatforms++;
}

bool *LevelUpdate::getIsPausedPointer()
{
    return &m_isPaused;
}

void LevelUpdate::positionLevelAtStart()
{
    float startOffset = m_platformPositions[0]->position.x;
    for (int i = 0; i < m_numberOfPlatforms; ++i)
    {
        m_platformPositions[i]->position.x = i * 100 + startOffset;
        m_platformPositions[i]->position.y = 0;
        m_platformPositions[i]->size.x = 100;
        m_platformPositions[i]->size.y = 20;
    }

    m_playerPosition->position.x = m_platformPositions[m_numberOfPlatforms / 2]->position.x + 2;
    m_playerPosition->position.y = m_platformPositions[m_numberOfPlatforms / 2]->position.y - 22;

    m_moveRelativeToPlatform = m_numberOfPlatforms - 1;
    m_nextPlatformToMove = 0;
}

int LevelUpdate::getRandomNumber(int minHeight, int maxHeight)
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minHeight, maxHeight);

    int randomHeight = distribution(gen);

    return randomHeight;
}

void LevelUpdate::update(float timeSinceLastUpdate)
{
    if (m_isPaused)
        return;
    if (m_gameOver)
    {
        m_gameOver = false;
        *m_cameraTime = 0;
        m_timeSinceLastPlatform = 0;
        positionLevelAtStart();
    }

    *m_cameraTime += timeSinceLastUpdate;
    m_timeSinceLastPlatform += timeSinceLastUpdate;

    if (m_timeSinceLastPlatform > m_platformCreationInterval)
    {
        m_platformPositions[m_nextPlatformToMove]->position.y =
            m_platformPositions[m_moveRelativeToPlatform]->position.y + getRandomNumber(-40, 40);

        if (m_platformPositions[m_moveRelativeToPlatform]->position.y < m_platformPositions[m_nextPlatformToMove]->position.y)
        {
            m_platformPositions[m_nextPlatformToMove]->position.x =
                m_platformPositions[m_moveRelativeToPlatform]->position.x + m_platformPositions[m_moveRelativeToPlatform]->size.x + getRandomNumber(20, 40);
        }
        else
        {
            m_platformPositions[m_nextPlatformToMove]->position.x =
                m_platformPositions[m_moveRelativeToPlatform]->position.x + m_platformPositions[m_moveRelativeToPlatform]->size.x + getRandomNumber(0, 20);
        }
        m_platformPositions[m_nextPlatformToMove]->size.x = getRandomNumber(20, 200);
        m_platformPositions[m_nextPlatformToMove]->size.y = getRandomNumber(10, 20);

        m_platformCreationInterval = m_platformPositions[m_nextPlatformToMove]->size.x / 90;

        m_moveRelativeToPlatform = m_nextPlatformToMove;

        m_nextPlatformToMove++;

        if (m_nextPlatformToMove == m_numberOfPlatforms)
        {
            m_nextPlatformToMove = 0;
        }
        m_timeSinceLastPlatform = 0;
    }

    bool laggingBehind = true;

    for (auto platformPosition : m_platformPositions)
    {
        if (platformPosition->position.x < m_playerPosition->position.x)
        {
            laggingBehind = false;
            break;
        }
        else
        {
            laggingBehind = true;
        }
    }

    if (laggingBehind)
    {
        m_isPaused = true;
        m_gameOver = true;
        SoundEngine::pauseMusic();
    }
}