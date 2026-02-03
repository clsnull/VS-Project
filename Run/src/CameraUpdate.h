#pragma once

#include "Update.h"
#include "InputReceiver.h"
#include <SFML/Graphics.hpp>
#include <memory>

class CameraUpdate : public Update
{
private:
    sf::FloatRect m_position;
    sf::FloatRect *m_playerPosition;
    bool m_receiversInput = false;
    InputReceiver *m_inputrecevicer = nullptr;

public:
    sf::FloatRect *getPositionPointer();
    void handleInput();
    InputReceiver *gerInputReceiver();

    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate) override;
    void update(float fps) override;
    ~CameraUpdate();
};
