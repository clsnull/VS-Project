#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>


void updateBranches(int seed);

const int NUM_BARNCHES = 6;
sf::Sprite* branches[NUM_BARNCHES];

enum class side { LEFT, RIGHT, NONE };

side branchPositions[NUM_BARNCHES];

int main()
{
    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;
    const float TREE_HORIZONTAL_POSITION = 810;
    const float TREE_VERTICAL_POSITION = 0;
    const float PI = 3.1415926f;
    const std::string title = "hello";

    int score = 0;
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(sf::Vector2f(
        (WINDOW_WIDTH) / 2 - timeBarStartWidth / 2, 980
    ));
    sf::Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


    sf::Font font;
    if (!font.openFromFile("fonts/KOMIKAP_.ttf")) {
        std::cout << "字体文件加载失败" << std::endl;
    }
    sf::Text messageText(font);
    sf::Text scoreText(font);
    sf::Text fpsText(font);

    messageText.setString("Press Enter to Start!");
    scoreText.setString("Score = 0");
    fpsText.setString("FPS = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    fpsText.setCharacterSize(14);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    fpsText.setFillColor(sf::Color::White);
    
    scoreText.setPosition(sf::Vector2f(20, 20));

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin({
        textRect.position.x + textRect.size.x / 2.0f ,
        textRect.position.y + textRect.size.y / 2.0f
    });
    messageText.setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
    fpsText.setPosition({ 3000, 20});

    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BARNCHES; i++) {
        branches[i] = new sf::Sprite(textureBranch);
        branches[i] -> setPosition(sf::Vector2f(-2000, -2000));

        branches[i] -> setOrigin(sf::Vector2f(220, 20));
    }

    sf::Vector2u vec(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::VideoMode vm(vec);
    sf::RenderWindow window(vm, title);

    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("graphics/background.png")) {
        std::cout << "图片加载失败" << std::endl;
    }
    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(sf::Vector2f(0, 0));

    sf::Texture textureTree;
    if (!textureTree.loadFromFile("graphics/tree.png")) {
        std::cout << "图片加载失败" << std::endl;
    }
    sf::Sprite spriteTree(textureTree);
    spriteTree.setPosition(sf::Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee(textureBee);
    spriteBee.setPosition(sf::Vector2f(0, 800));

    bool beeActive = false;
    
    float beeSpeed = 0.0f;

    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    sf::Sprite spriteCloud1(textureCloud);
    sf::Sprite spriteCloud2(textureCloud);
    sf::Sprite spriteCloud3(textureCloud);

    spriteCloud1.setPosition(sf::Vector2f(0, 0));
    spriteCloud2.setPosition(sf::Vector2f(0, 250));
    spriteCloud3.setPosition(sf::Vector2f(0, 500));

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    float cloud3Angle = 0.0f;
    float cloud3Amplitude = 50.0f;
    float cloud3Frequency = 2.0f;
    float cloud3OriginalY = 0.0f;

    bool paused = true;

    sf::Clock clock;

    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(sf::Vector2f(580, 720));

    side playerSide = side::LEFT;

    sf::Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    sf::Sprite spriteRIP(textureRIP);
    spriteRIP.setPosition(sf::Vector2f(600, 860));

    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    sf::Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(sf::Vector2f(700, 830));

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    sf::Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    sf::Sprite spriteLog(textureLog);
    spriteLog.setPosition(sf::Vector2f(810, 720));

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput = false;

    sf::SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    sf::Sound chop(chopBuffer);

    sf::SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/chop.wav");
    sf::Sound death(deathBuffer);
        
    sf::SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    sf::Sound outOfTime(ootBuffer);

    sf::Clock fpsClock;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::KeyReleased>() && !paused) {
                std::cout << "按键释放" << std::endl;
                acceptInput = true;

                spriteAxe.setPosition({ 2000, spriteAxe.getPosition().y });
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            paused = false;
            
            score = 0;
            timeRemaining = 6.0f;

            for (int i = 0; i < NUM_BARNCHES; i++) {
                branchPositions[i] = side::NONE;
            }

            spriteRIP.setPosition(sf::Vector2f(675, 2000));

            spritePlayer.setPosition(sf::Vector2f(580, 720));

            acceptInput = true;
        }

        if (acceptInput) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                std::cout << "按下右键" << std::endl;

                playerSide = side::RIGHT;
            
                score++;

                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(sf::Vector2f(AXE_POSITION_RIGHT, spriteAxe.getPosition().y));

                spritePlayer.setPosition({ 1200, 720 });

                updateBranches(score);

                spriteLog.setPosition({ 810, 720 });
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;

                chop.play();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                std::cout << "按下左键" << std::endl;
                playerSide = side::LEFT;

                score++;

                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(sf::Vector2f(AXE_POSITION_LEFT, spriteAxe.getPosition().y));

                spritePlayer.setPosition({ 580, 720 });

                updateBranches(score);

                spriteLog.setPosition({ 810, 720 });
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;

                chop.play();
            }
        }

        window.clear();

        sf::Time dt = clock.restart();

        if (!paused) {

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                paused = true;

                messageText.setString("Out of time!");
                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin({
                    textRect.position.x + textRect.size.x / 2.0f ,
                    textRect.position.y + textRect.size.y / 2.0f
                    });
                messageText.setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

                outOfTime.play();
            }

            if (!beeActive) {
                srand((int)std::time(0));
                beeSpeed = (rand() % 200) + 200;

                srand((int)std::time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(sf::Vector2f(2000, height));
                beeActive = true;
            }
            else {
                spriteBee.setPosition(
                    sf::Vector2f(
                        spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                        spriteBee.getPosition().y
                    )
                );
                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }

            if (!cloud1Active) {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(sf::Vector2f(-200, height));
                cloud1Active = true;
            }
            else {
                spriteCloud1.setPosition(
                    sf::Vector2f(
                        spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                        spriteCloud1.getPosition().y
                    )
                );
                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            if (!cloud2Active) {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(sf::Vector2f(-200, height));
                cloud2Active = true;
            }
            else {
            spriteCloud2.setPosition(
                    sf::Vector2f(
                        spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                        spriteCloud2.getPosition().y
                    )
                );
                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            if (!cloud3Active) {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(sf::Vector2f(-200, height));

                cloud3OriginalY = height;
                cloud3Angle = 0.0f;
                cloud3Amplitude = (rand() % 30) + 30.0f;
                cloud3Frequency = (rand() % 3) + 1.0f;

                cloud3Active = true;
            }
            else {
                cloud3Angle += cloud3Frequency * dt.asSeconds();
                float verticalOffset = cloud3Amplitude * sin(cloud3Angle);


                spriteCloud3.setPosition(
                    sf::Vector2f(
                        spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                        cloud3OriginalY + verticalOffset
                    )
                );
                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BARNCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    branches[i]->setPosition({ 610, height });
                    branches[i]->setRotation(sf::degrees(180));
                }
                else if (branchPositions[i] == side::RIGHT) {
                    branches[i]->setPosition({ 1330, height });
                    branches[i]->setRotation(sf::degrees(0));
                }
                else {
                    branches[i]->setPosition({ 3000, height });
                }
            }
            if (logActive) {
                spriteLog.setPosition({
                    spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
                });

                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
                    logActive = false;
                    spriteLog.setPosition({810, 720});
                }
            }
            if (branchPositions[5] == playerSide) {
                paused = true;
                acceptInput = false;
                spriteRIP.setPosition({ 525, 760 });

                spritePlayer.setPosition({ 2000, 660});

                messageText.setString("SQUISHED!!!");

                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin({
                    textRect.position.x + textRect.size.x / 2.0f,
                    textRect.position.y + textRect.size.y / 2.0f,
                });
                messageText.setPosition({ 1920 / 2.0f, 1080 / 2.0f });

                death.play();
            }
        }

        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            std::stringstream fps;
            fps << "FPS = " << (1 / dt.asSeconds());
            fpsText.setString(fps.str());

            sf::FloatRect fpsRect = fpsText.getLocalBounds();
            fpsText.setOrigin({
                fpsRect.position.x + fpsRect.size.x,
                fpsRect.position.y
                });
            fpsText.setPosition({ WINDOW_WIDTH - 10, 10 });

            fpsClock.restart();
        }

        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        for (int i = 0; i < NUM_BARNCHES; i++) {
            window.draw(*branches[i]);
        }

        window.draw(spriteTree);
        window.draw(timeBar);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);

        window.draw(spriteBee);

        window.draw(scoreText);
        window.draw(fpsText);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }
    for (int i = 0; i < NUM_BARNCHES; i++) {
        delete branches[i];
    }
    return 0;
}

void updateBranches(int seed) {
    for (int j = NUM_BARNCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    std::srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}