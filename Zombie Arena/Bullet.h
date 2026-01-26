#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Vector2f m_position;
	sf::RectangleShape m_bulletShape;
	bool m_inFlight = false;

	float m_bulletSpeed = 1000;

	float m_bulletDistanceX;
	float m_bulletDistanceY;

	float m_maxX;
	float m_minX;
	float m_maxY;
	float m_minY;
public:
	Bullet();
	//停止子弹飞行
	void stop();

	bool isInFlight();
	//发射子弹
	void shoot(float startX, float startY, float targetX, float targetY);
	//获取子弹位置
	sf::FloatRect getPosition();
	//获取子弹形状
	sf::RectangleShape& getShape();
	//更新子弹位置
	void update(float elapsedTime);
};

