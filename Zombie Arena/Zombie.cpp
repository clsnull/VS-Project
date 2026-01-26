#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>


void Zombie::spawn(float startX, float startY, int type, int seed) {
	switch (type)
	{
	case 0:
		m_sprite = std::make_unique<sf::Sprite>(TextureHolder::getTexture("graphics/bloater.png"));
		m_speed = BLOATER_SPEED;
		m_health = BLOATER_HEALTH;
		break;
	case 1:
		m_sprite = std::make_unique<sf::Sprite>(TextureHolder::getTexture("graphics/chaser.png"));
		m_speed = CHASER_SPEED;
		m_health = CHASER_HEALTH;
		break;
	case 2:
		m_sprite = std::make_unique<sf::Sprite>(TextureHolder::getTexture("graphics/crawler.png"));
		m_speed = CRAWLER_SPEED;
		m_health = CRAWLER_HEALTH;
		break;
	}
	std::srand((int)time(0) * seed);

	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;

	modifier /= 100;

	m_speed *= modifier;

	m_position.x = startX;
	m_position.y = startY;

	m_sprite->setOrigin({25, 25});

	m_sprite->setPosition(m_position);
}

bool Zombie::hit() {
	m_health--;
	if (m_health <= 0) {
		m_alive = false;
		m_sprite->setTexture(TextureHolder::getTexture("graphics/blood.png"));
	}
	return m_alive;
}

bool Zombie::isAlive() {
	return m_alive;
}

sf::FloatRect Zombie::getPosition() {
	return m_sprite->getGlobalBounds();
}

sf::Sprite& Zombie::getSprite() {
	return *m_sprite;
}

void Zombie::update(float elapsedTime, sf::Vector2f playerPosition) {
	float playerX = playerPosition.x;
	float playerY = playerPosition.y;

	if(playerX > m_position.x) {
		m_position.x += m_speed * elapsedTime;
	}
	if(playerY > m_position.y) {
		m_position.y += m_speed * elapsedTime;
	}
	if(playerX < m_position.x) {
		m_position.x -= m_speed * elapsedTime;
	}
	if(playerY < m_position.y) {
		m_position.y -= m_speed * elapsedTime;
	}

	m_sprite->setPosition(m_position);

	float angle = (atan2(playerY - m_position.y, playerX - m_position.x) * 180) / 3.14159;

	m_sprite->setRotation(sf::degrees(angle));
}
