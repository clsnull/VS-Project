#pragma once
#include "Graphics.h"

class Animator;
class PlayerUpdate;

class FireballGraphics : public Graphics
{
private:
    sf::FloatRect *m_Position;
    int m_VertexStartIndex;
    bool *m_FacingRight = nullptr;
    Animator *m_Animator;
    sf::IntRect *m_SectionToDraw;
    std::shared_ptr<PlayerUpdate> m_PlayerUpdate;

public:
    // From Graphics : Component
    void draw(sf::VertexArray &canvas) override;
    void assemble(sf::VertexArray &canvas,
                  std::shared_ptr<Update> genericUpdate,
                  sf::IntRect texCoords) override;
};
