#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(int type) :m_type(type)
{
	if (m_type == 1)
	{
		m_sprite = std::make_unique<sf::Sprite>(TextureHolder::getTexture("graphics/health_pickup.png"));
		m_value = HEALTH_START_VALUE;
	}
	else
	{
		m_sprite = std::make_unique<sf::Sprite>(TextureHolder::getTexture("graphics/ammo_pickup.png"));
		m_value = AMMO_START_VALUE;
	}
	m_sprite->setOrigin({25, 25});
	m_secondsToLive = START_SECONDS_TO_LIVE;
	m_secondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(sf::IntRect arena)
{
	m_arena.position.x = arena.position.x + 50;
	m_arena.position.y = arena.position.y + 50;

	m_arena.size.x = arena.size.x - 50;
	m_arena.size.y = arena.size.y - 50;
	spawn();
}

void Pickup::spawn()
{
	srand((int)time(0) / m_type);
	int x = (rand() % m_arena.size.x);
	srand((int)time(0) * m_type);
	int y = (rand() % m_arena.size.y);
	m_secondsSinceSpawn = 0;
	m_spawned = true;
	m_sprite->setPosition(sf::Vector2f( x, y ));
}

sf::FloatRect Pickup::getPosition() const
{
	return m_sprite->getGlobalBounds();
}

sf::Sprite& Pickup::getSprite() const
{
	return *m_sprite;
}

bool Pickup::isSpawned() const
{
	return m_spawned;
}

int Pickup::gotIt()
{
	m_spawned = false;
	m_secondsSinceDeSpawn = 0;
	return m_value;
}

void Pickup::update(float elapsedTime)
{
	if (m_spawned) {
		m_secondsSinceSpawn += elapsedTime;
	}
	else {
		m_secondsSinceDeSpawn += elapsedTime;
	}

	if(m_secondsSinceSpawn > m_secondsToLive && m_spawned) {
		m_spawned = false;
		m_secondsSinceDeSpawn = 0;
	}


	if(m_secondsSinceDeSpawn > m_secondsToWait && !m_spawned) {
		spawn();
	}
}

void Pickup::upgrade()
{
	if (m_type == 1)
	{
		m_value += (HEALTH_START_VALUE * .5);
	}
	else
	{
		m_value += (AMMO_START_VALUE * .5);
	}

	m_secondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_secondsToWait -= (START_WAIT_TIME / 10);
}