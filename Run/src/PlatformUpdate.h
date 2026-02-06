#pragma once

#include "Update.h"
#include <SFML/Graphics.hpp>

class PlatformUpdate : public Update
{
private:
    sf::FloatRect m_position;
    sf::FloatRect *m_playerPosition = nullptr;
    bool *m_playerIsGrounded = nullptr;

public:
    sf::FloatRect *getPositionPointer();
    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate) override;
    void update(float timeSinceLastUpdate) override;
};
