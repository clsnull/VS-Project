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

    m_position.size.x = PLAYER_WIDTH;
    m_position.size.y = PLAYER_HEIGHT;

    m_isPaused = levelUpdate->getIsPausedPointer();
}

void PlayerUpdate::handleInput()
{
    for (std::optional event : m_inputReceiver.getEvents())
    {
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::D)
            {
                m_rightIsHeldDown = true;
            }
            if (keyPressed->code == sf::Keyboard::Key::A)
            {
                m_leftIsHeldDown = true;
            }
            if (keyPressed->code == sf::Keyboard::Key::W)
            {
                m_boostIsHeldDown = true;
            }
            if (keyPressed->code == sf::Keyboard::Key::Space)
            {
                m_spaceHeldDown = true;
            }
        }
        if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->code == sf::Keyboard::Key::D)
            {
                m_rightIsHeldDown = false;
            }
            if (keyReleased->code == sf::Keyboard::Key::A)
            {
                m_leftIsHeldDown = false;
            }
            if (keyReleased->code == sf::Keyboard::Key::W)
            {
                m_boostIsHeldDown = false;
            }
            if (keyReleased->code == sf::Keyboard::Key::Space)
            {
                m_spaceHeldDown = false;
            }
        }
    }
    m_inputReceiver.clearEvents();
}

void PlayerUpdate::update(float timeTakenThisFrame)
{
    if (!*m_isPaused)
    {
        // 没有暂停
        m_position.position.y += m_gravity * timeTakenThisFrame;
        handleInput();
        if (m_isGrounded)
        {
            if (m_rightIsHeldDown)
            {
                m_position.position.x += timeTakenThisFrame * m_runspeed;
            }
            if (m_leftIsHeldDown)
            {
                m_position.position.x -= timeTakenThisFrame * m_runspeed;
            }
        }
        if (m_boostIsHeldDown)
        {
            m_position.position.y -= timeTakenThisFrame * m_boostspeed;
            if (m_rightIsHeldDown)
            {
                m_position.position.x += timeTakenThisFrame * m_runspeed / 2;
            }
            if (m_leftIsHeldDown)
            {
                m_position.position.x -= timeTakenThisFrame * m_runspeed / 4;
            }
        }
        if (m_spaceHeldDown && !m_inJump && m_isGrounded)
        {
            // SoundEngine::playJump();
            m_inJump = true;
            m_jumpClock.restart();
        }
        if (!m_spaceHeldDown)
        {
            // m_inJump = false;
        }
        if (m_inJump)
        {
            if (m_jumpClock.getElapsedTime().asSeconds() < m_jumpDuration / 2)
            {
                m_position.position.y -= m_jumpSpeed * timeTakenThisFrame;
            }
            else
            {
                m_position.position.y += m_jumpSpeed * timeTakenThisFrame;
            }

            if (m_jumpClock.getElapsedTime().asSeconds() > m_jumpDuration)
            {
                m_inJump = false;
            }
            if (m_rightIsHeldDown)
            {
                m_position.position.x += timeTakenThisFrame * m_runspeed;
            }
            if (m_leftIsHeldDown)
            {
                m_position.position.x -= timeTakenThisFrame * m_runspeed;
            }
        }
        m_isGrounded = false;
    }
}