#include "Bullet.h"

Bullet::Bullet()
{
	m_bulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
	m_inFlight = true;

	m_position.x = startX;
	m_position.y = startY;

	float gradient = (startX - targetX) / (startY - targetY);

	//任何小于1的斜率都需要取反
	if(gradient < 0) {
		gradient *= -1;
	}

	float ratioXY = m_bulletSpeed / (1 + gradient);


	m_bulletDistanceX = ratioXY * gradient;
	m_bulletDistanceY = ratioXY;

	if (targetX < startX)
	{
		m_bulletDistanceX *= -1;
	}
	if(targetY < startY)
	{
		m_bulletDistanceY *= -1;
	}
	float range = 1000;
	m_minX = startX - range;
	m_maxX = startX + range;
	m_minY = startY - range;
	m_maxY = startY + range;

	m_bulletShape.setPosition(m_position);
}

void Bullet::stop()
{
	m_inFlight = false;
}

bool Bullet::isInFlight()
{
	return m_inFlight;
}

sf::FloatRect Bullet::getPosition()
{
	return m_bulletShape.getGlobalBounds();
}

sf::RectangleShape& Bullet::getShape()
{
	return m_bulletShape;
}

void Bullet::update(float elapsedTime)
{
	m_position.x += m_bulletDistanceX * elapsedTime;
	m_position.y += m_bulletDistanceY * elapsedTime;
	m_bulletShape.setPosition(m_position);
	if (m_position.x < m_minX || m_position.x > m_maxX ||
		m_position.y < m_minY || m_position.y > m_maxY)
	{
		m_inFlight = false;
	}
}