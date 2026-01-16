#include "Ball.h"

Ball::Ball(float startX, float startY) :m_position(startX, startY) {
	m_shape.setSize(sf::Vector2f(10, 10));
	m_shape.setPosition(m_position);
}

sf::FloatRect Ball::getPosition() {
	return m_shape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape() {
	return m_shape;
}

float Ball::getXVelocity() {
	return m_directionX;
}

void Ball::reboundSides() {
	m_directionX = -m_directionX;
}

void Ball::reboundBatOrTop() {
	m_directionY = -m_directionY;
}

void Ball::reboundBottom() {
	m_position.y = 0;
	m_position.x = 500;
	m_directionY = -m_directionY;
}

void Ball::update(sf::Time dt) {
	m_position.y += m_directionY * m_speed * dt.asSeconds();
	m_position.x += m_directionX * m_speed * dt.asSeconds();

	m_shape.setPosition(m_position);
}