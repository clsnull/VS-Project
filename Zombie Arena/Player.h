#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	// 玩家位置
	sf::Vector2f m_position;
	// 精灵
	sf::Sprite m_sprite;
	// 纹理
	sf::Texture m_texture;
	//屏幕分辨率是多少
	sf::Vector2f m_resoultion;
	//当前场景的大小
	sf::IntRect m_arena;
	// 场景的每个图块（tile)有多大
	int m_tileSize;
	//玩家正在向那个方向移动
	bool m_upPressed;
	bool m_downPressed;
	bool m_leftPressed;
	bool m_rightPressed;
	// 玩家有多少生命值 
	int m_health;
	// 玩家最多能拥有的生命值是多少
	int m_maxHealth;
	// 玩家最后一次受击是什么时候
	sf::Time m_lastHit;
	// 速度
	float m_speed;
public:
	Player();
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	void resetPlayerStats();
	bool hit(sf::Time timeHit);
	sf::Time getLastHitTime();
	sf::FloatRect getPosition();
	sf::Vector2f getCenter();
	sf::Angle getRotation();
	sf::Sprite getSprite();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime, sf::Vector2i mousePosition);
	void upgradeSpeed();
	void upgradHealth();

	void increaseHealthLevel(int amount);
	int getHealth();
};