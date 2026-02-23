#include "MenuUpdate.h"
#include "LevelUpdate.h"
#include "PlayerUpdate.h"
#include "SoundEngine.h"

MenuUpdate::MenuUpdate(sf::RenderWindow *window)
{
    m_window = window;
}

sf::FloatRect *MenuUpdate::getPositionPointer()
{
    return &m_position;
}

bool *MenuUpdate::getGameOverPointer()
{
    return &m_gameOver;
}

InputReceiver *MenuUpdate::getInputReceiver()
{
    return &m_inputReceiver;
}

void MenuUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate)
{
    m_playerPosition =
        playerUpdate->getPositionPointer();
    m_isPaused =
        levelUpdate->getIsPausedPointer();

    m_position.size.x = 75;
    m_position.size.y = 75;

    SoundEngine::startMusic();
    SoundEngine::pauseMusic();
}

void MenuUpdate::handleInput()
{

    for (const std::optional event : m_inputReceiver.getEvents())
    {

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::F1 && m_isVisible)
            {
                if (SoundEngine::mMusicIsPlaying)
                {
                    SoundEngine::stopMusic();
                }
                m_window->close();
            }
        }

        if (const auto *KeyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if (KeyReleased->code == sf::Keyboard::Key::Escape)
            {
                m_isVisible = !m_isVisible;
                *m_isPaused = !*m_isPaused;

                if (m_gameOver)
                {
                    m_gameOver = false;
                }

                if (!*m_isPaused)
                {
                    SoundEngine::resumeMusic();
                    SoundEngine::playClick();
                }

                if (*m_isPaused)
                {
                    SoundEngine::pauseMusic();
                    SoundEngine::playClick();
                }
            }
        }
    }

    m_inputReceiver.clearEvents();
}

void MenuUpdate::update(float fps)
{
    handleInput();

    if (*m_isPaused && !m_isVisible) //  Game  over  1
    {
        m_isVisible = true;
        m_gameOver = true;
    }

    if (m_isVisible)
    {
        //  Follow  the player
        m_position.position.x =
            m_playerPosition->position.x - m_position.size.x / 2;
        m_position.position.y =
            m_playerPosition->position.y - m_position.size.y / 2;
    }
    else
    {
        m_position.position.x = -999;
        m_position.position.y = -999;
    }
}
