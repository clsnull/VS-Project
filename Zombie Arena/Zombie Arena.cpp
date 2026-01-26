#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie Arena.h"

int main()
{
    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    State state = State::GAME_OVER;

    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().size.x;
    resolution.y = sf::VideoMode::getDesktopMode().size.y;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(resolution.x, resolution.y)), "ZombieArena");
    sf::View mainView(sf::FloatRect(sf::Vector2f(0, 0), resolution));

    sf::Clock clock;

    sf::Time gameTimeTotal;

    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;
    Player player;

    sf::IntRect arena;

    sf::VertexArray background;

    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("graphics/background_sheet.png"))
    {
        std::cout << "¼ÓÔØ±³¾°Ê§°Ü" << std::endl;
    }

    while (window.isOpen())
    {

        while (std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::KeyPressed>())
            {
                sf::Keyboard::Key code = event->getIf<sf::Event::KeyPressed>()->code;

                if (code == sf::Keyboard::Key::Enter && state == State::PLAYING)
                {
                    state = State::PAUSED;
                    std::cout << "ÓÎÏ·ÔÝÍ£\n";
                }
                else if (code == sf::Keyboard::Key::Enter && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                    std::cout << "ÓÎÏ·PLAYING\n";
                }
                else if (code == sf::Keyboard::Key::Enter && state == State::GAME_OVER)
                {
                    std::cout << "ÓÎÏ·LEVELING_UP\n";
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING)
                {
                }

                if (state == State::LEVELING_UP)
                {
                    // Handle  the player  LEVELING  up
                    if (code == sf::Keyboard::Key::Num1)
                    {
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num2)
                    {
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num3)
                    {
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num4)
                    {
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num5)
                    {
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num6)
                    {
                        state = State::PLAYING;
                    }

                    if (state == State::PLAYING)
                    {
                        arena.size.x = 500;
                        arena.size.y = 500;
                        arena.position.x = 0;
                        arena.position.y = 0;
                        // We  will modify  this  line  of  code  later
                        int tileSize = createBackground(background, arena);
                        // Spawn  the player  in middle  of  the  arena
                        std::cout << "spawn" << std::endl;
                        player.spawn(arena, resolution, tileSize);

                        // Reset  clock  so  there  isn't  a frame jump
                        clock.restart();
                    }
                } //  End  LEVELING  up
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        if (state == State::PLAYING)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                std::cout << "moveUp\n";
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                std::cout << "moveDown\n";
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                std::cout << "moveLeft\n";
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                std::cout << "moveRight\n";
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

            sf::Time dt = clock.restart();

            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = sf::Mouse::getPosition();

            mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

            player.update(dtAsSeconds, sf::Mouse::getPosition());

            sf::Vector2f playerPosition(player.getCenter());

            mainView.setCenter(player.getCenter());
        }

        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            window.draw(player.getSprite());
        }
        window.display();
    }
    return 0;
}