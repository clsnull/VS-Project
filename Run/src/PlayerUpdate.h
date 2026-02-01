#pragma once
#include <SFML/Graphics.hpp>

#include "Update.h"

#include "InputReceiver.h"

class PlayerUpdate : public Update
{
private:
    const float PLAYER_WIDTH = 20.0f;
    const float PLAYER_HEIGHT = 16.0f;

    sf::FloatRect m_position;

    bool *m_isPaused = nullptr;
    float m_gravity = 165;
    float m_runspeed = 150;
    float m_boostspeed = 250;

    InputReceiver m_inputReceiver;

    sf::Clock m_jumpClock;

    bool m_spaceHeldDown = false;
    float m_jumpDuration = .50;
    float m_jumpSpeed = 400;

public:
    bool m_rightIsHeldDown = false;
    bool m_leftIsHeldDown = false;
    bool m_boostIsHeldDown = false;

    bool m_isGrounded;
    bool m_inJump = false;

    sf::FloatRect *getPositionPointer();
    bool *getGroundedPointer();
    void handleInput();
    InputReceiver *getInputReceiver();
    void assemble(
        std::shared_ptr<LevelUpdate> LevelUpdate,
        std::shared_ptr<PlayerUpdate> PlayerUpdate) override;
    void update(float fps) override;
};