#include "Bat.h"

Bat::Bat(float startX, float startY) :m_position(startX, startY) {
	m_shape.setSize(sf::Vector2f(120, 5));
	m_shape.setPosition(m_position);
}

sf::FloatRect Bat::getPositin() {
	return m_shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape() {
	return m_shape;
}

void Bat::moveRight() {
	m_moving_right = true;
}

void Bat::moveLeft() {
	m_moving_left = true;
}

void Bat::stopRight() {
	m_moving_right = false;
}

void Bat::stopLeft() {
	m_moving_left = false;
}

void Bat::update(sf::Time dt) {
	if (m_moving_left) {
		m_position.x -= m_speed * dt.asSeconds();
	}
	if (m_moving_right) {
		m_position.x += m_speed * dt.asSeconds();
	}
	m_shape.setPosition(m_position);
}