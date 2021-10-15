#include <SFML/Graphics.hpp>

#include "game.hpp"

int
main(int argc, char** argv)
{
    srand(std::time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "SMinesweeper");

    auto gameOverText
        = sf::Text("Game Over\nPress Space to restart",
                   sp::ResourceManager::getFont(RESOURCES_DIR "FreeMono.otf"));
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2
                               + gameOverText.getGlobalBounds().left,
                           gameOverText.getGlobalBounds().height / 2
                               + gameOverText.getGlobalBounds().top);
    gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    initGame();

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        if(!gameOver) {
            for(int i = 0; i < buttons.size(); i++) {
                buttons[i]->update(window);
                window.draw(*buttons[i]);
            }
        } else if(gameWon) {
            gameOverText.setString("Game Won");
            gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2
                                       + gameOverText.getGlobalBounds().left,
                                   gameOverText.getGlobalBounds().height / 2
                                       + gameOverText.getGlobalBounds().top);
            gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            window.draw(gameOverText);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
               && window.hasFocus()) {
                initGame();
            }
        } else {
            window.draw(gameOverText);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
               && window.hasFocus()) {
                initGame();
            }
        }
        window.draw(remainingMinesText);
        window.display();
    }

    return EXIT_SUCCESS;
}