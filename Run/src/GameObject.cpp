#include <SFML/Graphics.hpp>
#include <vector>

#include "GameObject.h"

#include "Graphics.h"
#include "Update.h"

void GameObject::addComponent(std::shared_ptr<Component> newComponent)
{
    m_components.push_back(newComponent);
}

void GameObject::update(float elapsedTime)
{
    for (auto component : m_components)
    {
        if (component->m_isUpdate)
        {
            std::static_pointer_cast<Update>(component)->update(elapsedTime);
        }
    }
}

void GameObject::draw(sf::VertexArray &canvas)
{
    for (auto component : m_components)
    {
        if (component->m_isGraphics)
        {
            std::static_pointer_cast<Graphics>(component)->draw(canvas);
        }
    }
}