#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.h"

class Update;

class GameObject
{
private:
    std::vector<std::shared_ptr<Component>> m_components;

public:
    void addComponent(std::shared_ptr<Component> newComponent);
    void update(float elapsedTime);
    void draw(sf::VertexArray &canvas);
};