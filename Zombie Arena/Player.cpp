#include "Player.h"
#include <cmath>
#include <iostream>
#include "TextureHolder.h"

Player::Player()
	: m_speed(START_SPEED),
	m_health(START_HEALTH),
	m_maxHealth(START_HEALTH)
{
	m_texture = TextureHolder::getTexture("graphics/player.png");
	m_sprite = std::make_unique<sf::Sprite>(m_texture);
	m_sprite->setOrigin(sf::Vector2f(25, 25));
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
	m_position.x = arena.size.x / 2;
	m_position.y = arena.size.y / 2;

	m_arena.position.x = arena.position.x;
	m_arena.position.y = arena.position.y;
	m_arena.size.x = arena.size.x;
	m_arena.size.y = arena.size.y;

	m_tileSize = tileSize;

	m_resoultion.x = resolution.x;
	m_resoultion.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_speed = START_SPEED;
	m_health = START_HEALTH;
	m_maxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime()
{
	return m_lastHit;
}

bool Player::hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200)
	{
		m_lastHit = timeHit;
		m_health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

sf::FloatRect Player::getPosition()
{
	return m_sprite->getGlobalBounds();
}

sf::Vector2f Player::getCenter()
{
	return m_position;
}

sf::Angle Player::getRotation()
{
	return m_sprite->getRotation();
}

int Player::getHealth()
{
	return m_health;
}

void Player::moveLeft()
{
	m_leftPressed = true;
}

void Player::moveRight()
{
	m_rightPressed = true;
}

void Player::moveUp()
{
	m_upPressed = true;
}

void Player::moveDown()
{
	m_downPressed = true;
}

void Player::stopLeft()
{
	m_leftPressed = false;
}

void Player::stopRight()
{
	m_rightPressed = false;
}

void Player::stopUp()
{
	m_upPressed = false;
}

void Player::stopDown()
{
	m_downPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
	if (m_upPressed)
	{
		m_position.y -= m_speed * elapsedTime;
	}
	if (m_downPressed)
	{
		m_position.y += m_speed * elapsedTime;
	}
	if (m_rightPressed)
	{
		m_position.x += m_speed * elapsedTime;
	}
	if (m_leftPressed)
	{
		m_position.x -= m_speed * elapsedTime;
	}

	m_sprite->setPosition(m_position);

	if (m_position.x > m_arena.size.x - m_tileSize)
	{
		m_position.x = m_arena.size.x - m_tileSize;
	}
	if (m_position.x < m_arena.position.x + m_tileSize)
	{
		m_position.x = m_arena.position.x + m_tileSize;
	}
	if (m_position.y > m_arena.size.y - m_tileSize)
	{
		m_position.y = m_arena.size.y - m_tileSize;
	}
	if (m_position.y < m_arena.position.y + m_tileSize)
	{
		m_position.y = m_arena.position.y + m_tileSize;
	}

	float angle = (atan2(mousePosition.y - m_resoultion.y / 2, mousePosition.x - m_resoultion.x / 2) * 180) / 3.141;

	m_sprite->setRotation(sf::degrees(angle));
}

void Player::upgradeSpeed()
{
	m_speed += (START_SPEED * 0.2);
}
void Player::upgradHealth()
{
	m_maxHealth += (START_HEALTH * 0.2);
}

void Player::increaseHealthLevel(int amount)
{
	m_health += amount;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

sf::Sprite& Player::getSprite()
{
	return *m_sprite;
}