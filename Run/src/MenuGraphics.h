#pragma once
#include "Graphics.h"

class MenuGraphics : public Graphics
{
private:
    sf::FloatRect *m_menuPosition = nullptr;
    int m_vertexStartIndex;
    bool *m_gameOver;
    bool m_currentStatus = false;

    int uPos;
    int vPos;
    int texWidth;
    int texHeight;

public:
    // 从Graphics：Component继承
    void draw(sf::VertexArray &canvas) override;
    void assemble(sf::VertexArray &canvas,
                  std::shared_ptr<Update> genericUpdate,
                  sf::IntRect texCoords) override;
};
