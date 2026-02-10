
#include "PlatformGraphics.h"
#include "PlatformUpdate.h"

void PlatformGraphics::assemble(
    sf::VertexArray &canvas,
    std::shared_ptr<Update> genericUpdate,
    sf::IntRect texCoords)
{

    std::shared_ptr<PlatformUpdate> platformUpdate = std::static_pointer_cast<PlatformUpdate>(genericUpdate);
    m_position = platformUpdate->getPositionPointer();
    m_vertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 6);

    const int uPos = texCoords.position.x;
    const int vPos = texCoords.position.y;
    const int texWidth = texCoords.size.x;
    const int texHeight = texCoords.size.y;

    canvas[m_vertexStartIndex].texCoords.x = uPos;
    canvas[m_vertexStartIndex].texCoords.y = vPos;
    canvas[m_vertexStartIndex + 1].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 1].texCoords.y = vPos;
    canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight;

    canvas[m_vertexStartIndex + 3].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 3].texCoords.y = vPos;
    canvas[m_vertexStartIndex + 4].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight;
    canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight;
}

void PlatformGraphics::draw(sf::VertexArray &canvas)
{
    const sf::Vector2f &position = m_position->position;
    const sf::Vector2f &scale = m_position->size;
    // 左上
    canvas[m_vertexStartIndex].position = position;
    // 右上
    canvas[m_vertexStartIndex + 1].position = position + sf::Vector2f(scale.x, 0);
    // 左下
    canvas[m_vertexStartIndex + 2].position = position + sf::Vector2f(0, scale.y);

    // 右上
    canvas[m_vertexStartIndex + 3].position = position + sf::Vector2f(scale.x, 0);
    // 右下
    canvas[m_vertexStartIndex + 4].position = position + scale;
    // 左下
    canvas[m_vertexStartIndex + 5].position = position + sf::Vector2f(0, scale.y);
}