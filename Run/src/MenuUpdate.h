#pragma once

#include "Update.h"
#include "InputReceiver.h"
#include <SFML/Graphics.hpp>

class MenuUpdate : public Update
{
private:
    sf::FloatRect m_position;
    InputReceiver m_inputReceiver;
    sf::FloatRect *m_playerPosition = nullptr;

    bool m_isVisible = false;
    bool *m_isPaused;
    bool m_gameOver;
    sf::RenderWindow *m_window;

public:
    MenuUpdate(sf::RenderWindow *window);
    void handleInput();
    sf::FloatRect *getPositionPointer();
    bool *getGameOverPointer();
    InputReceiver *getInputReceiver();

    // From  Update  :  Component
    void update(float fps) override;
    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate)
        override;
};
