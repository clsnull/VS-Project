#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::VideoMode vm({ 1920, 1080 });
	sf::Window window(vm, "Pong");
	while (window.isOpen()) {
		window.display();
	}
	return 0;
}
