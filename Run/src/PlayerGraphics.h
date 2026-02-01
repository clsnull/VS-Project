#pragma once

#include "Graphics.h"
#include <SFML/Graphics.hpp>

class PlayerUpdate;

class PlayerGraphics : public Graphics
{
private:
    sf::FloatRect *m_position = nullptr;
    int m_vertexStartIndex = -999;

    sf::IntRect *m_sectionToDraw = new sf::IntRect;
    sf::IntRect *m_standingStillSectionToDraw = new sf::IntRect;

    std::shared_ptr<PlayerUpdate> m_playerUpdate;

    const int BOOST_TEX_LEFT = 536;
    const int BOOST_TEX_TOP = 0;
    const int BOOST_TEX_WIDTH = 69;
    const int BOOST_TEX_HEIGHT = 100;

    bool m_lastFacingRight = true;

public:
    void assemble(
        sf::VertexArray &canvas,
        std::shared_ptr<Update> genericUpdate,
        sf::IntRect texCoords) override;
    void draw(sf::VertexArray &canvas) override;
};