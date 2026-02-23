#include <iostream>
#include <memory>

#include "Factory.h"

#include "LevelUpdate.h"
#include "PlayerGraphics.h"
#include "PlayerUpdate.h"
#include "InputDispatcher.h"

#include "CameraUpdate.h"
#include "CameraGraphics.h"

#include "PlatformUpdate.h"
#include "PlatformGraphics.h"

#include "MenuUpdate.h"
#include "MenuGraphics.h"

#include "RainGraphics.h"

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

    for (int i = 0; i < 8; i++)
    {
        GameObject platform;
        std::shared_ptr<PlatformUpdate> platformUpdate = std::make_shared<PlatformUpdate>();
        platformUpdate->assemble(nullptr, playerUpdate);
        platform.addComponent(platformUpdate);

        std::shared_ptr<PlatformGraphics> platformGraphics = std::make_shared<PlatformGraphics>();
        platformGraphics->assemble(
            canvas,
            platformUpdate,
            sf::IntRect({PLATFORM_TEX_LEFT, PLATFORM_TEX_TOP}, {PLATFORM_TEX_WIDTH, PLATFORM_TEX_HEIGHT}));
        platform.addComponent(platformGraphics);
        gameObjects.push_back(platform);

        levelUpdate->addPlatformPosition(platformUpdate->getPositionPointer());
    }

    const float width = float(sf::VideoMode::getDesktopMode().size.x);
    const float height = float(sf::VideoMode::getDesktopMode().size.y);
    const float ratio = width / height;

    GameObject camera;
    std::shared_ptr<CameraUpdate> cameraUpdate = std::make_shared<CameraUpdate>();
    cameraUpdate->assemble(nullptr, playerUpdate);
    camera.addComponent(cameraUpdate);

    std::shared_ptr<CameraGraphics> cameraGraphics = std::make_shared<CameraGraphics>(
        m_window,
        m_texture,
        sf::Vector2f(CAM_VIEW_WIDTH, CAM_VIEW_WIDTH / ratio),
        sf::FloatRect({CAM_SCREEN_RATIO_LEFT, CAM_SCREEN_RATIO_TOP}, {CAM_SCREEN_RATIO_WIDTH, CAM_SCREEN_RATIO_HEIGHT}));

    cameraGraphics->assemble(
        canvas,
        cameraUpdate,
        sf::IntRect({CAM_TEX_LEFT, CAM_TEX_TOP}, {CAM_TEX_WIDTH, CAM_TEX_HEIGHT}));

    camera.addComponent(cameraGraphics);

    gameObjects.push_back(camera);

    levelUpdate->connectToCameraTime(
        cameraGraphics->getTimeConnection());

    GameObject mapCamera;
    std::shared_ptr<CameraUpdate> mapCameraUpdate = std::make_shared<CameraUpdate>();
    mapCameraUpdate->assemble(nullptr, playerUpdate);
    mapCamera.addComponent(mapCameraUpdate);

    inputDispatcher.registerNewInputReceiver(mapCameraUpdate->gerInputReceiver());

    std::shared_ptr<CameraGraphics> mapCameraGraphics = std::make_shared<CameraGraphics>(
        m_window,
        m_texture,
        sf::Vector2f(MAP_CAM_VIEW_WIDTH, MAP_CAM_VIEW_WIDTH / ratio),
        sf::FloatRect({MAP_CAM_SCREEN_RATIO_LEFT, MAP_CAM_SCREEN_RATIO_TOP},
                      {MAP_CAM_SCREEN_RATIO_WIDTH, MAP_CAM_SCREEN_RATIO_HEIGHT}));

    mapCameraGraphics->assemble(
        canvas,
        mapCameraUpdate,
        sf::IntRect({MAP_CAM_TEX_LEFT, MAP_CAM_TEX_TOP}, {MAP_CAM_TEX_WIDTH, MAP_CAM_TEX_HEIGHT}));

    mapCamera.addComponent(mapCameraGraphics);
    gameObjects.push_back(mapCamera);

    GameObject menu;
    std::shared_ptr<MenuUpdate> menuUpdate = std::make_shared<MenuUpdate>(m_window);
    menuUpdate->assemble(levelUpdate, playerUpdate);

    inputDispatcher.registerNewInputReceiver(menuUpdate->getInputReceiver());

    menu.addComponent(menuUpdate);

    std::shared_ptr<MenuGraphics> menuGraphics = std::make_shared<MenuGraphics>();

    menuGraphics->assemble(canvas, menuUpdate,
                           sf::IntRect({TOP_MENU_TEX_LEFT, TOP_MENU_TEX_TOP}, {TOP_MENU_TEX_WIDTH, TOP_MENU_TEX_HEIGHT}));

    menu.addComponent(menuGraphics);
    gameObjects.push_back(menu);

    int rainCoveragePerObject = 25;
    int areaToCover = 350;

    for (int h = -areaToCover / 2; h < areaToCover / 2;
         h += rainCoveragePerObject)
    {
        for (int v = -areaToCover / 2; v < areaToCover / 2;
             v += rainCoveragePerObject)
        {
            GameObject rain;

            std::shared_ptr<RainGraphics> rainGraphics =
                std::make_shared<RainGraphics>(
                    playerUpdate->getPositionPointer(), h, v, rainCoveragePerObject);

            rainGraphics->assemble(
                canvas, nullptr,
                sf::IntRect({RAIN_TEX_LEFT, RAIN_TEX_TOP}, {RAIN_TEX_WIDTH, RAIN_TEX_HEIGHT}));
            rain.addComponent(rainGraphics);
            gameObjects.push_back(rain);
        }
    }
}