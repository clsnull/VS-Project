#include "RainGraphics.h"
#include "RainGraphics.h"
#include "Animator.h"

RainGraphics::RainGraphics(
    sf::FloatRect* playerPosition,
    float horizontalOffset,
    float verticalOffset,
    int rainCoveragePerObject)
{
    m_playerPosition = playerPosition;
    m_horizontalOffset = horizontalOffset;
    m_verticalOffset = verticalOffset;

    m_scale.x = rainCoveragePerObject;
    m_scale.y = rainCoveragePerObject;
}

void RainGraphics::assemble(sf::VertexArray& canvas,
                            std::shared_ptr<Update> genericUpdate,
                            sf::IntRect texCoords) 
{
    m_animator = new Animator(
        texCoords.position.x,
        texCoords.position.y,
        4, // 帧数
        texCoords.size.x * 4,
        texCoords.size.y,
        8); // 帧率

    m_vertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 6);
}

void RainGraphics::draw(sf::VertexArray& canvas) 
{
    const sf::Vector2f& position = m_playerPosition->position - sf::Vector2f(m_scale.x / 2 + m_horizontalOffset, m_scale.y / 2 + m_verticalOffset);

    // 移动雨以跟上玩家
    canvas[m_vertexStartIndex].position = position;
    canvas[m_vertexStartIndex + 1].position = position + sf::Vector2f(m_scale.x, 0);
    canvas[m_vertexStartIndex + 2].position = position + sf::Vector2f(0, m_scale.y);
    
    canvas[m_vertexStartIndex + 3].position = position + sf::Vector2f(m_scale.x, 0);
    canvas[m_vertexStartIndex + 4].position = position + m_scale;
    canvas[m_vertexStartIndex + 5].position = position + sf::Vector2f(0, m_scale.y);

    m_sectionToDraw = m_animator->getCurrentFrame(false);

    // 记住要绘制的纹理部分
    const int uPos = m_sectionToDraw->position.x;
    const int vPos = m_sectionToDraw->position.y;
    const int texWidth = m_sectionToDraw->position.x;
    const int texHeight = m_sectionToDraw->position.y;

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

