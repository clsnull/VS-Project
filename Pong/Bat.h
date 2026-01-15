#pragma once
#include <SFML/Graphics.hpp>


class Bat
{
public:
	Bat(float startX, float startY);
	sf::FloatRect getPositin();
	sf::RectangleShape getShape();
	void moveRight();
	void moveLeft();
	void stopLeft();
	void stopRight();
	void update(sf::Time dt);

private:
	sf::Vector2f m_position;
	sf::RectangleShape m_shape;

	float m_speed = 1000.0f;
	bool m_moving_right = false;
	bool m_moving_left = false;
};

