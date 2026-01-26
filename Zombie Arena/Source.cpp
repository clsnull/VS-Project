#include "Zombie Arena.h"

#include "Zombie.h"

Zombie * createHorde(int numZombies, sf::IntRect arena) {
	Zombie* zombies = new Zombie[numZombies];
	int maxY = arena.size.y - 20;
	int minY = arena.position.y + 20;
	int maxX = arena.size.x - 20;
	int minX = arena.position.x + 20;

	for(int i = 0; i < numZombies; i++) {
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side) {
		case 0:
				x = minX;
				y = (rand() % maxY) + minY;
				break;
		case 1:
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		srand((int)time(0) * i * 2);
		int type = (rand() % 3);

		zombies[i].spawn(x, y, type, i);
	}
}