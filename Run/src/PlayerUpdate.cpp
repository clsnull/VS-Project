#include <SFML/Graphics.hpp>

#include "PlayerUpdate.h"

#include "SoundEngine.h"
#include "LevelUpdate.h"

sf::FloatRect *PlayerUpdate::getPositionPointer()
{
    return &m_position;
}

bool *PlayerUpdate::getGroundedPointer()
{
    return &m_isGrounded;
}

InputReceiver *PlayerUpdate::getInputReceiver()
{
    return &m_inputReceiver;
}

void PlayerUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate)
{
    SoundEngine::SoundEngine();

    // m_position.size.x = PLAYER_WIDTH;
    // m_position.size.y = PLAYER_HEIGHT;
    // 临时代码
    m_position.size.x = PLAYER_WIDTH * 10;
    m_position.size.y = PLAYER_HEIGHT * 10;

    m_isPaused = levelUpdate->getIsPausedPointer();
}

void PlayerUpdate::handleInput()
{
    m_inputReceiver.clearEvents();
}

void PlayerUpdate::update(float timeTakenThisFrame)
{
    handleInput();
}