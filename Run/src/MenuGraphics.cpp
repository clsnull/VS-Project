#include "MenuGraphics.h"
#include "MenuUpdate.h"

void MenuGraphics::assemble(sf::VertexArray &canvas,
                            std::shared_ptr<Update> genericUpdate,
                            sf::IntRect texCoords)
{
    m_menuPosition = std::static_pointer_cast<MenuUpdate>(genericUpdate)->getPositionPointer();
    m_gameOver = std::static_pointer_cast<MenuUpdate>(genericUpdate)->getGameOverPointer();
    m_currentStatus = *m_gameOver;
    m_vertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 6);

    // 记住UV坐标
    // 因为我们稍后会对它们进行操作
    uPos = texCoords.position.x;
    vPos = texCoords.position.y;
    texWidth = texCoords.size.x;
    texHeight = texCoords.size.y;

    canvas[m_vertexStartIndex].texCoords.x = uPos;
    canvas[m_vertexStartIndex].texCoords.y = vPos + texHeight;

    canvas[m_vertexStartIndex + 1].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 1].texCoords.y = vPos + texHeight;

    canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight + texHeight;

    
    canvas[m_vertexStartIndex + 3].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 3].texCoords.y = vPos + texHeight;
    
    canvas[m_vertexStartIndex + 4].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight + texHeight;

    canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight + texHeight;
}

void MenuGraphics::draw(sf::VertexArray& canvas)
{
    if (*m_gameOver && !m_currentStatus)
    {
        // 当前状态刚刚切换为游戏结束
        m_currentStatus = *m_gameOver;

        // 每个v坐标都加倍以引用下面的纹理
        canvas[m_vertexStartIndex].texCoords.x = uPos;
        canvas[m_vertexStartIndex].texCoords.y = vPos + texHeight;
        canvas[m_vertexStartIndex + 1].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 1].texCoords.y = vPos + texHeight;
        canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight + texHeight;
        
        canvas[m_vertexStartIndex + 3].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 3].texCoords.y = vPos + texHeight;
        canvas[m_vertexStartIndex + 4].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight + texHeight;
        canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight + texHeight;
    }
    else if (!*m_gameOver && m_currentStatus)
    {
        m_currentStatus = *m_gameOver;
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

    const sf::Vector2f& position = m_menuPosition->position;
    canvas[m_vertexStartIndex].position = position;
    canvas[m_vertexStartIndex + 1].position = position + sf::Vector2f(m_menuPosition->size.x, 0);
    canvas[m_vertexStartIndex + 2].position = position + sf::Vector2f(0, m_menuPosition->size.y);

    canvas[m_vertexStartIndex + 3].position = position + sf::Vector2f(m_menuPosition->size.x, 0);
    canvas[m_vertexStartIndex + 4].position = position + m_menuPosition->size;
    canvas[m_vertexStartIndex + 5].position = position + sf::Vector2f(0, m_menuPosition->size.y);
}
