#pragma once
#include <SFML/Graphics.hpp>

class Animator
{
private:
    sf::IntRect m_sourceRect;
    int m_leftOffset;
    int m_frameCount;
    int m_curentFrame;
    int m_framePeriod;
    int m_frameWidth;
    int m_fps = 12;
    sf::Clock m_clock;

public:
    Animator(int leftOffset, int topOffset, int frameCount,
             int textureWidth, int textureHeight, int fps);
    sf::IntRect *getCurrentFrame(bool reversed);
};