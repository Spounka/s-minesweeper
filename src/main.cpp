#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.hpp"
#include "config.hpp"
#include "resourcesmanager.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 10;
const int MINES = 39;

bool expanded = false;
std::vector<sp::Button*> buttons(FIELD_WIDTH* FIELD_HEIGHT);
std::vector<int> mines(FIELD_WIDTH* FIELD_HEIGHT, 0);
auto gameOver = false;

int
expand_button(int index)
{
    int numberOfMines = 0;
    int x = index % FIELD_WIDTH;
    int y = index / FIELD_HEIGHT;

    for(int i = -1; i < 2; i++) {
        bool yWithinBounds = (y + i >= 0) && (y + i < FIELD_HEIGHT);
        for(int j = -1; j < 2; j++) {
            bool xWithinBounds = (x + j >= 0) && (x + j < FIELD_WIDTH);
            int neighbourMine = (y + i) * FIELD_WIDTH + (x + j);
            if(xWithinBounds && yWithinBounds) {
                if(mines[neighbourMine] == -1 && neighbourMine != index)
                    numberOfMines++;
            }
        }
    }
    return numberOfMines;
}

void
onButtonClick(void* args = nullptr)
{
    int index = *(static_cast<int*>(args));
    int numberOfMines = 0;
    if(!expanded) {
        expanded = true;
        int i = 0;
        while(i < MINES) {
            int randPos = rand() % (FIELD_WIDTH * FIELD_HEIGHT);
            if(randPos == index || mines[randPos] == -1) {
                continue;
            }
            mines[randPos] = -1;
            i++;
        }
    } else if(mines[index] == -1) {
        std::cout << "BOOOOM\n";
        buttons[index]->setString("B");
        gameOver = true;
        return;
    }
    numberOfMines = expand_button(index);
    buttons[index]->setString(std::to_string(numberOfMines));
    buttons[index]->Enable(false);
    buttons[index]->setTexture(
        sp::ResourceManager::getTexture(RESOURCES_DIR "button_clicked.png"));
}

int
main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "SMinesweeper");

    {
        sp::Button button(
            sp::ResourceManager::getTexture(RESOURCES_DIR "Button2.png"));
        auto sizeX = button.getTextureRect().width;
        auto sizeY = button.getTextureRect().height;

        for(int i = 0; i < FIELD_WIDTH; i++) {
            for(int j = 0; j < FIELD_HEIGHT; j++) {
                int index = j * FIELD_WIDTH + i;
                buttons[index] = dynamic_cast<sp::Button*>(button.clone());
                buttons[index]->setPosition(
                    sf::Vector2f(sizeX * i + sizeX, sizeY * j + sizeY));
                buttons[index]->setString("");
                buttons[index]->SetID(index);
                buttons[index]->onClick(&onButtonClick,
                                        &buttons[index]->getID());
            }
        }
    }

    auto gameOverText
        = sf::Text("Game Over",
                   sp::ResourceManager::getFont(RESOURCES_DIR "FreeMono.otf"));
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2
                               + gameOverText.getGlobalBounds().left,
                           gameOverText.getGlobalBounds().height / 2
                               + gameOverText.getGlobalBounds().top);
    gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
        } else {
            window.draw(gameOverText);
        }

        window.display();
    }

    for(int i = 0; i < buttons.size(); i++) {
        delete buttons[i];
    }

    return EXIT_SUCCESS;
}