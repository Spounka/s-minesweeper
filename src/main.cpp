#include <SFML/Graphics.hpp>
#include <iostream>

int
main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SMinesweeper");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return EXIT_SUCCESS;
}