#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
	sf::Vector2f m_position;
	sf::RectangleShape m_shape;
	float m_speed = 300.0f;
	float m_directionX = .2f;
	float m_directionY = .2f;
public:
	Ball(float startX, float startY);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	float getXVelocity();
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void update(sf::Time dt);
};