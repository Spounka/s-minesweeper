#include <SFML/Graphics.hpp>

#include "game.hpp"

int
main(int argc, char** argv)
{
    srand(std::time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "SMinesweeper");


    initGame();

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        updateGame(window);
        window.display();
    }

    return EXIT_SUCCESS;
}