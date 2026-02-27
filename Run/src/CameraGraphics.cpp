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

    //  Initialize  the  background  sprites
    if(!m_backgroundTexture.loadFromFile("graphics/backgroundTexture.png")){
        std::cout << "加载失败" << std::endl;
    }
    m_backgroundSprite = std::make_unique<sf::Sprite>(m_backgroundTexture);
    m_backgroundSprite2 = std::make_unique<sf::Sprite>(m_backgroundTexture);

    m_backgroundSprite->setPosition({0, -200});

    //  Initialize  the  shader
    if(!m_shader.loadFromFile("shaders/glslsandbox109644", sf::Shader::Type::Fragment)){
        std::cout << "加载失败" << std::endl;
    }

    if (!m_shader.isAvailable())
    {
        std::cout << "The shader is not available\n";
    }
    m_shader.setUniform("resolution", sf::Vector2f(2500, 2500));
    m_shaderClock.restart();
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

    ///  Background  stuff
    sf::Vector2f movement;
    movement.x = m_position->position.x - m_playersPreviousPosition.x;
    movement.y = m_position->position.y - m_playersPreviousPosition.y;

    if (m_backgrounsAreFlipped)
    {
        m_backgroundSprite2->setPosition({
            m_backgroundSprite2->getPosition().x + movement.x / 6,
            m_backgroundSprite2->getPosition().y + movement.y / 6
        });

        m_backgroundSprite->setPosition({
            m_backgroundSprite2->getPosition().x + m_backgroundSprite2->getTextureRect().size.x,
            static_cast<float>(m_backgroundSprite2->getTextureRect().position.y)
        });

        if (m_position->position.x > 
            m_backgroundSprite->getPosition().x +
                (m_backgroundSprite->getTextureRect().size.x / 2))
        {
            m_backgrounsAreFlipped = !m_backgrounsAreFlipped;
            m_backgroundSprite2->setPosition(m_backgroundSprite->getPosition());
        }
    }
    else
    {
        // cout  << mBackgrounsAreFlipped  <<  endl;
        m_backgroundSprite->setPosition({
            m_backgroundSprite->getPosition().x - movement.x /  6,
            m_backgroundSprite->getPosition().y + movement.y / 6});

        m_backgroundSprite2->setPosition({
            m_backgroundSprite->getPosition().x + m_backgroundSprite->getTextureRect().size.x,
            m_backgroundSprite->getPosition().y
        });

        if (m_position->position.x >
            m_backgroundSprite2->getPosition().x +
                (m_backgroundSprite2->getTextureRect().size.x / 2))
        {
            m_backgrounsAreFlipped = !m_backgrounsAreFlipped;
            m_backgroundSprite->setPosition(
                m_backgroundSprite2->getPosition());
        }
    }

    m_playersPreviousPosition.x = m_position->position.x;
    m_playersPreviousPosition.y = m_position->position.y;

    // Set  the  others parameters  who //need  to  be  updated  every frame
    m_shader.setUniform("time", m_shaderClock.getElapsedTime().asSeconds());

    sf::Vector2i mousePos = m_window->mapCoordsToPixel(m_position->position);
    m_shader.setUniform("mouse", sf::Vector2f(mousePos.x, mousePos.y + 1000));

    if (m_shaderClock.getElapsedTime().asSeconds() > 10)
    {
        m_shaderClock.restart();
        m_showShader = !m_showShader;
    }

    if (!m_showShader)
    {
        m_window->draw(*m_backgroundSprite, &m_shader);
        m_window->draw(*m_backgroundSprite2, &m_shader);
    }
    else // Show  the parallax  background
    {
        m_window->draw(*m_backgroundSprite);
        m_window->draw(*m_backgroundSprite2);
    }

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