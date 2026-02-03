#include "CameraGraphics.h"

#include "CameraUpdate.h"
#include "PlayerUpdate.h"
#include "LevelUpdate.h"
#include <iostream>
#include <memory>

CameraGraphics::CameraGraphics(
    sf::RenderWindow *window,
    sf::Texture *texture,
    sf::Vector2f viewSize,
    sf::FloatRect viewport)
{
    m_window = window;
    m_texture = texture;
    m_view.setSize(viewSize);
    m_view.setViewport(viewport);

    if (viewport.size.x < 1)
    {
        m_isMiniMap = true;
    }
    else
    {
        if (!m_font.openFromFile("fonts/KOMIKAP_.ttf"))
        {
            std::cout << "字段加载失败" << std::endl;
        }
        m_text = new sf::Text(m_font);
        m_text->setFont(m_font);
        m_text->setFillColor(sf::Color(255, 0, 0, 255));
        m_text->setScale({0.2f, 0.2f});
    }
}

void CameraGraphics::assemble(
    sf::VertexArray &canvas,
    std::shared_ptr<Update> genericUpdate,
    sf::IntRect texCoords)
{
    std::shared_ptr<CameraUpdate> cameraUpdate = std::static_pointer_cast<CameraUpdate>(genericUpdate);
    m_position = cameraUpdate->getPositionPointer();
    m_vertexStartIndex = canvas.getVertexCount();

    canvas.resize(canvas.getVertexCount() + 6);

    const int uPos = texCoords.position.x;
    const int vPos = texCoords.position.y;
    const int texWidth = texCoords.size.x;
    const int texHeight = texCoords.size.y;

    // 左上
    canvas[m_vertexStartIndex].texCoords.x = uPos;
    canvas[m_vertexStartIndex].texCoords.y = vPos;
    // 右上
    canvas[m_vertexStartIndex + 1].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 1].texCoords.y = vPos;
    // 左下
    canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight;

    // 右上
    canvas[m_vertexStartIndex + 3].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 3].texCoords.y = vPos;

    // 右下
    canvas[m_vertexStartIndex + 4].texCoords.x = uPos + texWidth;
    canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight;

    // 左下
    canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
    canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight;
}

float *CameraGraphics::getTimeConnection()
{
    return &m_time;
}

void CameraGraphics::draw(sf::VertexArray &canvas)
{
    m_view.setCenter(m_position->getCenter());

    sf::Vector2f startPosition;

    startPosition.x = m_view.getCenter().x - m_view.getSize().x / 2;
    startPosition.y = m_view.getCenter().y - m_view.getSize().y / 2;

    sf::Vector2f scale;
    scale.x = m_view.getSize().x;
    scale.y = m_view.getSize().y;
    // 左上
    canvas[m_vertexStartIndex].position = startPosition;
    // 右上
    canvas[m_vertexStartIndex + 1].position = startPosition + sf::Vector2f(scale.x, 0);
    // 左下
    canvas[m_vertexStartIndex + 2].position = startPosition + sf::Vector2f(0, scale.y);

    // 右上
    canvas[m_vertexStartIndex + 3].position = startPosition + sf::Vector2f(scale.x, 0);
    // 右下
    canvas[m_vertexStartIndex + 4].position = startPosition + scale;
    // 左下
    canvas[m_vertexStartIndex + 5].position = startPosition + sf::Vector2f(0, scale.y);

    if (m_isMiniMap)
    {
        if (m_view.getSize().x < MAX_WIDTH && m_position->size.x > 1)
        {
            m_view.zoom(m_position->size.x);
        }
        else if (m_view.getSize().x > MIN_WIDTH && m_position->size.x < 1)
        {
            m_view.zoom(m_position->size.x);
        }
    }
    m_window->setView(m_view);

    if (!m_isMiniMap)
    {
        m_text->setString(std::to_string(m_time));
        m_text->setPosition(m_window->mapPixelToCoords(sf::Vector2i(5, 5)));
        m_window->draw(*m_text);
    }

    m_window->draw(canvas, m_texture);
}

CameraGraphics::~CameraGraphics()
{
    delete m_text;
}