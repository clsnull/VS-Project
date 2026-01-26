#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
private:
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 5;
	const int START_SECONDS_TO_LIVE = 5;

	std::unique_ptr<sf::Sprite> m_sprite;

	sf::IntRect m_arena;

	int m_value;

	int m_type;

	bool m_spawned;
	float m_secondsSinceSpawn;
	float m_secondsSinceDeSpawn;
	float m_secondsToLive;
	float m_secondsToWait;

public:
	Pickup(int type);
	void setArena(sf::IntRect arena);
	void spawn();
	sf::FloatRect getPosition() const;
	sf::Sprite& getSprite() const;
	void update(float elapsedTime);
	bool isSpawned() const;
	int gotIt();
	void upgrade();
};

