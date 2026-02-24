#pragma once

#include "Update.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class FireballUpdate : public Update
{
private:
    FloatRect m_position;

    FloatRect *m_playerPosition;
    bool *m_gameIsPaused = nullptr;
    float m_speed = 250;
    float m_range = 900;
    int m_maxSpawnDistanceFromPlayer = 250;

    bool m_movementPaused = true;
    Clock m_pauseClock;
    float m_pauseDurationTarget = 0;
    float m_maxPause = 6;
    float m_minPause = 1;
    // float mTimePaused  =  0;
    bool m_leftToRight = true;

public:
    FireballUpdate(bool *pausedPointer);
    bool *getFacingRightPointer();
    FloatRect *getPositionPointer();
    int getRandomNumber(int minHeight, int maxHeight);

    // 来自Update：Component
    void update(float fps) override;
    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate) override;
};
