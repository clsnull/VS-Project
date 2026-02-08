#pragma once

#include "Graphics.h"

class PlatformGraphics : public Graphics
{
private:
    sf::FloatRect *m_position = nullptr;
    int m_vertexStartIndex = -1;

public:
    void assemble(sf::VertexArray &canvas,
                  std::shared_ptr<Update> genericUpdate,
                  sf::IntRect texCoords) override;
    void draw(sf::VertexArray &canvas) override;
};
