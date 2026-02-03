#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class Update;
class Graphics : public Component
{
private:
public:
    Graphics();
    virtual void assemble(sf::VertexArray &canvas,
                          std::shared_ptr<Update> genericUpdate,
                          sf::IntRect texCoords) = 0;
    virtual void draw(sf::VertexArray &canvas) = 0;
};
