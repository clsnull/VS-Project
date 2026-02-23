#pragma once

#include "Graphics.h"

class Animator;

class RainGraphics : public Graphics
{
private:
    sf::FloatRect *m_playerPosition;

    int m_vertexStartIndex;
    sf::Vector2f m_scale;

    float m_horizontalOffset;
    float m_verticalOffset;

    Animator *m_animator;
    sf::IntRect *m_sectionToDraw;

public:
    RainGraphics(sf::FloatRect *playerPosition,
                 float horizontalOffset,
                 float verticalOffset,
                 int rainCoveragePerObject);

    // 来自Graphics：Component
    void draw(sf::VertexArray &canvas) override;
    void assemble(sf::VertexArray &canvas,
                  std::shared_ptr<Update> genericUpdate,
                  sf::IntRect texCoords) override;
};
