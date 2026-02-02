#include "PlayerGraphics.h"

#include "PlayerUpdate.h"

void PlayerGraphics::assemble(sf::VertexArray &canvas,
                              std::shared_ptr<Update> genericUpdate,
                              sf::IntRect texCoords)
{
    m_playerUpdate = std::static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_position = m_playerUpdate->getPositionPointer();

    m_vertexStartIndex = canvas.getVertexCount();

    canvas.resize(canvas.getVertexCount() + 6);

    // 左上
    canvas[m_vertexStartIndex].texCoords.x = texCoords.position.x;
    canvas[m_vertexStartIndex].texCoords.y = texCoords.position.y;
    // 右上
    canvas[m_vertexStartIndex + 1].texCoords.x = texCoords.position.x + texCoords.size.x;
    canvas[m_vertexStartIndex + 1].texCoords.y = texCoords.position.y;
    // 左下
    canvas[m_vertexStartIndex + 2].texCoords.x = texCoords.position.x;
    canvas[m_vertexStartIndex + 2].texCoords.y = texCoords.position.y + texCoords.size.y;

    // 右上
    canvas[m_vertexStartIndex + 3].texCoords.x = texCoords.position.x + texCoords.size.x;
    canvas[m_vertexStartIndex + 3].texCoords.y = texCoords.position.y;
    // 右下
    canvas[m_vertexStartIndex + 4].texCoords.x = texCoords.position.x + texCoords.size.x;
    canvas[m_vertexStartIndex + 4].texCoords.y = texCoords.position.y + texCoords.size.y;
    // 左下
    canvas[m_vertexStartIndex + 5].texCoords.x = texCoords.position.x;
    canvas[m_vertexStartIndex + 5].texCoords.y = texCoords.position.y + texCoords.size.y;
}

void PlayerGraphics::draw(sf::VertexArray &canvas)
{
    const sf::Vector2f &position = m_position->position;

    const sf::Vector2f &size = m_position->size;

    // 第一个三角形的位置
    canvas[m_vertexStartIndex].position = position;  // 左上
    canvas[m_vertexStartIndex + 1].position = sf::Vector2f(position.x + size.x, position.y);  // 右上
    canvas[m_vertexStartIndex + 2].position = sf::Vector2f(position.x, position.y + size.y);  // 左下

    // 第二个三角形的位置
    canvas[m_vertexStartIndex + 3].position = sf::Vector2f(position.x + size.x, position.y);  // 右上
    canvas[m_vertexStartIndex + 4].position = position + size;  // 右下
    canvas[m_vertexStartIndex + 5].position = sf::Vector2f(position.x, position.y + size.y);  // 左
}
