#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
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

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(resolution.x, resolution.y)), "ZombieArena", sf::State::Fullscreen);
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

    sf::Sprite spriteGameOver(TextureHolder::getTexture("graphics/background.png"));
    spriteGameOver.setPosition({0, 0});

    sf::View hubView(sf::FloatRect(sf::Vector2f(0, 0), {1920, 1080}));

	sf::Sprite spriteAmmoIcon(TextureHolder::getTexture("graphics/ammo_icon.png"));
	spriteAmmoIcon.setPosition({ 20, 980 });

	sf::Font font;
    if (!font.openFromFile("fonts/zombiecontrol.ttf")) {
        std::cout << "字体加载失败\n";
    }

    sf::Text pausedText(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(sf::Color::White);
    pausedText.setPosition({ 400, 400 });
	pausedText.setString("Game paused.\nPress Enter to continue.");

	sf::Text gameOverText(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition({ 250, 850 });
	gameOverText.setString("Game over.\nPress Enter to restart.");

	sf::Text levelUpText(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(sf::Color::White);
    levelUpText.setPosition({ 150, 250 });
	std::stringstream levelUpString;

    levelUpString <<    
        "1 -   Increased   rate  of  fire" <<
        "\n2 -  Increased   clip   size(next   reload)" <<
        "\n3 -   Increased  max   health" <<
        "\n4 -   Increased   run   speed" <<
        "\n5 -  More   and   better   health   pickups" <<
        "\n6 -  More   and   better   ammo   pickups";
    levelUpText.setString(levelUpString.str());

    // Ammo
    sf::Text ammoText(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setPosition({ 200, 980 });

    // Score
    sf::Text scoreText(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 20, 0 });

    //  Load  the  high  score from  a  text file
    std::ifstream inputFile("gamedata/scores.txt");
    if (inputFile.is_open())
    {
        //  >>  Reads  the  data
        inputFile >> hiScore;
        inputFile.close();
    }

    // Hi Score
    sf::Text hiScoreText(font);
    hiScoreText.setCharacterSize(55);
    hiScoreText.setFillColor(sf::Color::White);
    hiScoreText.setPosition({ 1400, 0 });

    std::stringstream s;
    s << "Hi   Score:" << hiScore;
    hiScoreText.setString(s.str());

    // Zombies  remaining
    sf::Text zombiesRemainingText(font);
    zombiesRemainingText.setCharacterSize(55);
    zombiesRemainingText.setFillColor(sf::Color::White);
    zombiesRemainingText.setPosition({ 1500, 980 });
    zombiesRemainingText.setString("Zombies:  100");

    // Wave  number
    int  wave = 0;
    sf::Text waveNumberText(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(sf::Color::White);
    waveNumberText.setPosition({ 1250, 980 });
    waveNumberText.setString("Wave:  0");

    // Health  bar
    sf::RectangleShape healthBar;
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition({ 450, 980 });

	int framesSinceLastHUDUpdate = 0;

	int fpsMeasurementFrameInterval = 1000;

	sf::SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	sf::Sound hitSound(hitBuffer);
    
    // Prepare  the  splat  sound
    sf::SoundBuffer  splatBuffer;
    splatBuffer.loadFromFile("sound/splat.wav");
    sf::Sound splatSound(splatBuffer);

    // Prepare  the  shoot  sound
    sf::SoundBuffer  shootBuffer;
    shootBuffer.loadFromFile("sound/shoot.wav");
    sf::Sound shoot(shootBuffer);

    // Prepare  the  reload  sound
    sf::SoundBuffer   reloadBuffer;
    reloadBuffer.loadFromFile("sound/reload.wav");
    sf::Sound reload(reloadBuffer);

    // Prepare  the failed  sound
    sf::SoundBuffer  reloadFailedBuffer;
    reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
    sf::Sound reloadFailed(reloadFailedBuffer);

    // Prepare  the powerup  sound
    sf::SoundBuffer   powerupBuffer;
    powerupBuffer.loadFromFile("sound/powerup.wav");
    sf::Sound powerup(powerupBuffer);

    // Prepare  the pickup  sound
    sf::SoundBuffer   pickupBuffer;
    pickupBuffer.loadFromFile("sound/pickup.wav");
    sf::Sound pickup(pickupBuffer);

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
                    wave = 0;
                    score = 0;

                    currentBullet = 0;
					bulletsSpare = 24;
                    bulletsInClip = 6;
					clipSize = 6;
					fireRate = 1;  

					player.resetPlayerStats();
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
							reloadFailed.play();
                        }
                    }
                }

                if (state == State::LEVELING_UP)
                {
                    // Handle  the player  LEVELING  up
                    if (code == sf::Keyboard::Key::Num1)
                    {
                        fireRate++;
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num2)
                    {
                        clipSize += clipSize;
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num3)
                    {
						player.upgradHealth();
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num4)
                    {
						player.upgradeSpeed();
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num5)
                    {
                        healthPickup.upgrade();
                        state = State::PLAYING;
                    }
                    if (code == sf::Keyboard::Key::Num6)
                    {
                        ammoPickup.upgrade();
                        state = State::PLAYING;
                    }

                    if (state == State::PLAYING)
                    {
                        wave++;
                        arena.size.x = 500 * wave;
                        arena.size.y = 500 * wave;
                        arena.position.x = 0;
                        arena.position.y = 0;
                        // We  will modify  this  line  of  code  later
                        int tileSize = createBackground(background, arena);
                        // Spawn  the player  in middle  of  the  arena
                        std::cout << "spawn" << std::endl;
                        player.spawn(arena, resolution, tileSize);

						healthPickup.setArena(arena);
						ammoPickup.setArena(arena);

                        numZombies = 5 * wave;

                        delete[] zombies;
						zombies = createHorde(numZombies, arena);
						numZombiesAlive = numZombies;

						powerup.play();

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
					shoot.play();
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
						splatSound.play();
                    }
                }
			}

            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive() == false) continue;

                if (player.getPosition().findIntersection(zombies[i].getPosition())) {
                    if (player.hit(gameTimeTotal)) {
                        hitSound.play();
                    }
                    if (player.getHealth() <= 0) {
                        state = State::GAME_OVER;
                        std::cout << "游戏结束\n";
                        std::ofstream outputFile("gamedata/scores.txt");
                        //  <<  writes  the  data
                        outputFile << hiScore;
                        outputFile.close();
                    }
                }
            }

            if (player.getPosition().findIntersection(healthPickup.getPosition()) && healthPickup.isSpawned()) {
				player.increaseHealthLevel(healthPickup.gotIt());
				pickup.play();
            }

            if (player.getPosition().findIntersection(ammoPickup.getPosition()) && ammoPickup.isSpawned()) {
				bulletsSpare += ammoPickup.gotIt();
                reload.play();
            }

            healthBar.setSize(sf::Vector2f( player.getHealth() * 3, 50 ));
			framesSinceLastHUDUpdate++;

            if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval) {
                std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
                std::stringstream ssWave;
                std::stringstream ssZombiesAlive;

				ssAmmo << bulletsInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				ssScore << "Score: " << score;
				scoreText.setString(ssScore.str());

				ssHiScore << "Hi   Score: " << hiScore;
                hiScoreText.setString(ssHiScore.str());

                ssWave << "Wave: " << wave;
                waveNumberText.setString(ssWave.str());

                ssZombiesAlive << "Zombies: " << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

                framesSinceLastHUDUpdate = 0;
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

            if (ammoPickup.isSpawned()) {
				window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned()) {
				window.draw(healthPickup.getSprite());
            }

			window.draw(spriteCrosshair);

            window.draw(player.getSprite());
			window.setView(hubView);
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
        }

        if (state == State::LEVELING_UP) {
            window.draw(spriteGameOver);
            window.draw(levelUpText);
        }

        if (state == State::PAUSED) {
            window.draw(pausedText);
        }

        if (state == State::GAME_OVER) {
            window.draw(spriteGameOver);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(hiScoreText);
        }

        window.display();
    }

	delete[] zombies;

    return 0;
}