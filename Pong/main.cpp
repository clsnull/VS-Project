#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdlib>

#include "Bat.h"
#include "Ball.h"

using namespace std;

int main()
{
	sf::VideoMode vm(sf::Vector2u(1920, 1080));
	sf::RenderWindow window(vm, "Pong");
	int score = 0;
	int lives = 3;

	Bat bat(1920 / 2, 1080 - 20);
	Ball ball(1920 / 2, 0);
	sf::Font font;
	if (font.openFromFile("fonts/DS-DIGIT.ttf")) {
		std::cout << "找不到文件" << std::endl;
	}
	sf::Text hub(font);
	hub.setCharacterSize(75);

	hub.setFillColor(sf::Color::White);
	hub.setPosition(sf::Vector2f(20, 20));

	sf::Clock clock;
	while (window.isOpen()) {
		// Handle the player input
		while (std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::KeyReleased>()) {
				std::cout << "按键释放" << std::endl;
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			bat.moveLeft();
		}
		else {
			bat.stopLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			bat.moveRight();
		}
		else {
			bat.stopRight();
		}
		// update the bat, the ball and the hub
		sf::Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);

		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hub.setString(ss.str());

		if (ball.getPosition().position.y > window.getSize().y) {
			ball.reboundBottom();
			lives--;
			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}
		if (ball.getPosition().position.y < 0) {
			ball.reboundBatOrTop();
			score++;
		}
		if (ball.getPosition().position.x < 0 || ball.getPosition().position.x + ball.getPosition().size.x > window.getSize().x) {
			ball.reboundSides();
		}
		bool collisionX = bat.getPositin().position.x + bat.getPositin().size.x >= ball.getPosition().position.x && ball.getPosition().position.x + ball.getPosition().size.x >= bat.getPositin().position.x;
		bool collisionY = bat.getPositin().position.y + bat.getPositin().size.y >= ball.getPosition().position.y && ball.getPosition().position.y + ball.getPosition().size.y >= bat.getPositin().position.y;
		if (collisionX && collisionY) {
			ball.reboundBatOrTop();
		}
		// Draw the bat, the ball and the hub
		window.clear();
		window.draw(hub);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}
	return 0;
}
