#include <iostream>
#include <memory>

#include "Factory.h"

#include "LevelUpdate.h"
#include "PlayerGraphics.h"
#include "PlayerUpdate.h"
#include "InputDispatcher.h"

Factory::Factory(sf::RenderWindow *window)
{
    m_window = window;
    m_texture = new sf::Texture();
    if (!m_texture->loadFromFile("graphics/texture.png"))
    {
        std::cout << "Texture not loaded";
        return;
    }
}

void Factory::loadLevel(
    std::vector<GameObject> &gameObjects,
    sf::VertexArray &canvas,
    InputDispatcher &inputDispatcher)
{
    GameObject level;
    std::shared_ptr<LevelUpdate> levelUpdate = std::make_shared<LevelUpdate>();
    level.addComponent(levelUpdate);
    gameObjects.push_back(level);

    GameObject player;
    std::shared_ptr<PlayerUpdate> playerUpdate = std::make_shared<PlayerUpdate>();
    playerUpdate->assemble(levelUpdate, nullptr);
    player.addComponent(playerUpdate);

    inputDispatcher.registerNewInputReceiver(playerUpdate->getInputReceiver());

    std::shared_ptr<PlayerGraphics> playerGraphics = std::make_shared<PlayerGraphics>();

    playerGraphics->assemble(
        canvas,
        playerUpdate,
        sf::IntRect({PLAYER_TEX_LEFT, PLAYER_TEX_TOP}, {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}));

    player.addComponent(playerGraphics);
    gameObjects.push_back(player);

    levelUpdate->assemble(nullptr, playerUpdate);
}