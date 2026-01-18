#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::VideoMode vm(sf::Vector2u(1920, 1080));
    sf::RenderWindow window(vm, "Zombie Arena");
    while (window.isOpen()) {
        window.display();
    }
    std::cout << "Hello World!\n";
}
