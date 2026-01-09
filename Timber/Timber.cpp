#include <SFML/Graphics.hpp>

int main()
{   
    sf::Vector2u vec(1920, 1080);
    sf::VideoMode vm(vec);
    sf::RenderWindow window(vm, "hello");
    return 0;
}
