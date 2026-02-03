#pragma once

#include <SFML/Graphics.hpp>
#include "Graphics.h"

class Update;

class CameraGraphics : public Graphics
{
private:
    sf::RenderWindow *m_window;
    sf::View m_view;
    int m_vertexStartIndex = -999;
    sf::Texture *m_texture = nullptr;
    sf::FloatRect *m_position = nullptr;
    bool m_isMiniMap = false;

    const float MIN_WIDTH = 640.0f;
    const float MAX_WIDTH = 2000.0f;

    sf::Text* m_text = nullptr;
    sf::Font m_font;
    int m_timeAtEndOfGame = 0;
    float m_time = 0;

public:
    CameraGraphics(
        sf::RenderWindow *window,
        sf::Texture * texture,
        sf::Vector2f viewSize,
        sf::FloatRect viewport);
    float *getTimeConnection();
    void assemble(sf::VertexArray &canvas,
                  std::shared_ptr<Update> genericUpdate,
                  sf::IntRect texCoords) override;
    void draw(sf::VertexArray &canvas) override;
    ~CameraGraphics();
};
