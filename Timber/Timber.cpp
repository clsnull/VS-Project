#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>

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

    messageText.setString("Press Enter to Start!");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);

    scoreText.setPosition(sf::Vector2f(20, 20));
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin({
        textRect.position.x + textRect.size.x / 2.0f ,
        textRect.position.y + textRect.size.y / 2.0f
    });
    messageText.setPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

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

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            paused = false;
            
            score = 0;
            timeRemaining = 6.0f;
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
        }
        
        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);
        window.draw(timeBar);

        window.draw(spriteBee);
        window.draw(spriteBee);

        window.draw(scoreText);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }
    return 0;
}
