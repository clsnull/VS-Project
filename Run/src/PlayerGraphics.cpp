#include "PlayerGraphics.h"

#include "PlayerUpdate.h"

void PlayerGraphics::assemble(sf::VertexArray &canvas,
                              std::shared_ptr<Update> genericUpdate,
                              sf::IntRect texCoords)
{
    m_playerUpdate = std::static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_position = m_playerUpdate->getPositionPointer();

    m_vertexStartIndex = canvas.getVertexCount();

    // TODO可能要改
    canvas.resize(canvas.getVertexCount() + 4);

    // 左上
    canvas[m_vertexStartIndex].texCoords.x = texCoords.position.x;
    canvas[m_vertexStartIndex].texCoords.y = texCoords.position.y;
    // 右上
    canvas[m_vertexStartIndex + 1].texCoords.x = texCoords.position.x + texCoords.size.x;
    canvas[m_vertexStartIndex + 1].texCoords.y = texCoords.position.y + texCoords.size.y;
    // 右下
    canvas[m_vertexStartIndex + 2].texCoords.x = texCoords.position.x + texCoords.size.x;
    canvas[m_vertexStartIndex + 2].texCoords.y = texCoords.position.x + texCoords.size.y;
    // 左下
    canvas[m_vertexStartIndex + 3].texCoords.x = texCoords.position.x;
    canvas[m_vertexStartIndex + 3].texCoords.y = texCoords.position.y + texCoords.size.y;
}

void PlayerGraphics::draw(sf::VertexArray &canvas)
{
    // TODO 有问题
    const sf::Vector2f &position = m_position->position;

    const sf::Vector2f &scale = m_position->size;

    canvas[m_vertexStartIndex].position = position;

    canvas[m_vertexStartIndex + 1].position = position + sf::Vector2f(scale.x, 0);

    canvas[m_vertexStartIndex + 2].position = position + scale;

    canvas[m_vertexStartIndex + 3].position = position + sf::Vector2f(0, scale.y);
}
