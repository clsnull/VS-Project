#include "Animator.h"

Animator::Animator(
    int leftOffset, int topOffset, int frameCount,
    int textureWidth, int textureHeight, int fps)
{
    m_leftOffset = leftOffset;
    m_curentFrame = 0;
    m_frameCount = frameCount;
    m_frameWidth = (float)textureWidth / m_frameCount;
    m_sourceRect.position.x = leftOffset;
    m_sourceRect.position.y = topOffset;
    m_sourceRect.size.x = m_frameWidth;
    m_sourceRect.size.y = textureHeight;
    m_fps = fps;
    m_framePeriod = 1000 / m_fps;
    m_clock.restart();
}

sf::IntRect *Animator::getCurrentFrame(bool reversed)
{
    if (m_clock.getElapsedTime().asMilliseconds() > m_framePeriod)
    {
        m_curentFrame++;
        if (m_curentFrame >= m_frameCount + reversed)
        {
            m_curentFrame = 0 + reversed;
        }
        m_clock.restart();
    }

    m_sourceRect.position.x = m_leftOffset + m_curentFrame * m_frameWidth;

    return &m_sourceRect;
}