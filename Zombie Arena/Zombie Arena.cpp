#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombie Arena.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"

int main()
{
    TextureHolder holder;

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

    sf::Texture textureBackground = TextureHolder::getTexture("graphics/background_sheet.png");

    int numZombies;
	int numZombiesAlive;

	Zombie* zombies = nullptr;

    Bullet bullets[100];
	int currentBullet = 0;
    int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	sf::Time lastPressed;

    window.setMouseCursorVisible(false);

    sf::Sprite spriteCrosshair(TextureHolder::getTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin({ 25, 25 });

	Pickup healthPickup(1);
	Pickup ammoPickup(2);

    int score = 0;
    int hiScore = 0;
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
                    std::cout << "游戏暂停\n";
                }
                else if (code == sf::Keyboard::Key::Enter && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                    std::cout << "游戏PLAYING\n";
                }
                else if (code == sf::Keyboard::Key::Enter && state == State::GAME_OVER)
                {
                    std::cout << "游戏LEVELING_UP\n";
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING)
                {
                    if (code == sf::Keyboard::Key::R) {
                        if(bulletsSpare >= clipSize) {
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                        } else if(bulletsSpare > 0) {
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        }
                        else {
							// 没有子弹了
                        }
                    }
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

						healthPickup.setArena(arena);
						ammoPickup.setArena(arena);

                        numZombies = 10;

                        delete[] zombies;
						zombies = createHorde(numZombies, arena);
						numZombiesAlive = numZombies;

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if(gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0) {
					bullets[currentBullet].shoot(
                        player.getCenter().x, player.getCenter().y, 
                        mouseWorldPosition.x, mouseWorldPosition.y
                    );
					currentBullet++;
                    if(currentBullet > 99) {
                        currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					bulletsInClip--;
				}
            }

            sf::Time dt = clock.restart();

            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = sf::Mouse::getPosition();

            mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

			spriteCrosshair.setPosition(mouseWorldPosition);

            player.update(dtAsSeconds, sf::Mouse::getPosition());

            sf::Vector2f playerPosition(player.getCenter());

            mainView.setCenter(player.getCenter());

            for (int i = 0; i < numZombies; i++) {
                if(zombies[i].isAlive()) {
                    zombies[i].update(dtAsSeconds, playerPosition);
				}
            }
            for (int i = 0; i < 100; i++) {
                if (bullets[i].isInFlight()) {
                    bullets[i].update(dtAsSeconds);
                }
            }

			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

            //碰撞检测
            for (int i = 0; i < 100; i++) {
                if(bullets[i].isInFlight() == false) {
                    continue;
                }
                for (int j = 0; j < numZombies; j++) {
                    if(zombies[j].isAlive() == false) {
                        continue;
					}
                    if (bullets[i].getPosition().findIntersection(zombies[j].getPosition())) {
						bullets[i].stop();

                        if (zombies[j].hit()) {
                            score += 10;
                            if (score >= hiScore) {
								hiScore = score;
                            }

                            numZombiesAlive--;

                            if(numZombiesAlive == 0) {
                                state = State::LEVELING_UP;
							}
                        }
                    }
                }
			}

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive() == false) continue;

                if (player.getPosition().findIntersection(zombies[i].getPosition())) {
                    if (player.hit(gameTimeTotal)) {

                    }
                    if (player.getHealth() <= 0) {
                        state = State::GAME_OVER;
                        std::cout << "游戏结束\n";
                    }
                }
            }

            if (player.getPosition().findIntersection(healthPickup.getPosition()) && healthPickup.isSpawned()) {
				player.increaseHealthLevel(healthPickup.gotIt());
            }

            if (player.getPosition().findIntersection(ammoPickup.getPosition()) && ammoPickup.isSpawned()) {
				bulletsSpare += ammoPickup.gotIt();
            }
        }

        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);

            for (int i = 0; i < numZombies; i++) {

                sf::RectangleShape healthBar;
                healthBar.setPosition(zombies[i].getPosition().position);
                healthBar.setSize(zombies[i].getPosition().size);
                healthBar.setFillColor(sf::Color::Red);
                window.draw(healthBar);

                window.draw(zombies[i].getSprite());
            }

            for(int i = 0; i < 100; i++) {
                if(bullets[i].isInFlight()) {
                    window.draw(bullets[i].getShape());
                }
			}

            sf::RectangleShape healthBar;
            healthBar.setPosition(player.getPosition().position);
            healthBar.setSize(player.getPosition().size);
            healthBar.setFillColor(sf::Color::Red);
            window.draw(healthBar);

            window.draw(player.getSprite());

            if (ammoPickup.isSpawned()) {
				window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned()) {
				window.draw(healthPickup.getSprite());
            }


			window.draw(spriteCrosshair);
        }

        window.display();
    }

	delete[] zombies;

    return 0;
}