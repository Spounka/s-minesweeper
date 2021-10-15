#include "game.hpp"
#include "config.hpp"
#include "resourcesmanager.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 10;
const int MAX_MINES = 20;
int remainingMines = MAX_MINES;
sf::Text remainingMinesText
    = sf::Text("Remaining mines: ",
               sp::ResourceManager::getFont(RESOURCES_DIR "FreeMono.otf"));
sf::Text gameOverText
    = sf::Text("", sp::ResourceManager::getFont(RESOURCES_DIR "FreeMono.otf"));

uint seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
std::uniform_int_distribution<int> distribution(0, FIELD_WIDTH* FIELD_HEIGHT);
auto randInt = std::bind(distribution, generator);

std::vector<std::unique_ptr<sp::Button>>
buttons(FIELD_WIDTH* FIELD_HEIGHT); // List of buttons
std::vector<int> mines(FIELD_WIDTH* FIELD_HEIGHT,
                       0); // < List of mines locations
std::vector<bool> expandedButtons(FIELD_WIDTH* FIELD_HEIGHT,
                                  false); // < List of buttons expanded
std::vector<bool> flaggedButtons(FIELD_WIDTH* FIELD_WIDTH,
                                 false); //< List of buttons marked as bomb

auto expanded = false;
auto gameOver = false;
auto gameWon = false;

void
updateRemainingMinesText()
{
    char text[25];
    std::sprintf(text, "Remaining mines: %d", remainingMines);
    remainingMinesText.setString(text);
}

int
expand_button(int index)
{
    int numberOfMines = 0;
    // * Conversion from 1D to 2D array
    int x = index % FIELD_WIDTH;  // * This is the column value
    int y = index / FIELD_HEIGHT; // * This is the row

    for(int i = -1; i < 2; i++) {
        bool yWithinBounds = (y + i >= 0) && (y + i < FIELD_HEIGHT);
        for(int j = -1; j < 2; j++) {
            bool xWithinBounds = (x + j >= 0) && (x + j < FIELD_WIDTH);
            int neighbourMine = (y + i) * FIELD_WIDTH + (x + j);
            if(xWithinBounds && yWithinBounds) {
                if(mines[neighbourMine] == -1 && neighbourMine != index) {
                    numberOfMines++;
                }
            }
        }
    }
    return numberOfMines;
}

void
checkForWinCondition()
{
    auto temp = true;
    for(int i = 0; i < mines.size(); i++) {
        if(!flaggedButtons[i] && mines[i] == -1) {
            temp = false;
            break;
        }
    }
    gameWon = temp;
    if(temp) {
        gameOverText.setString("Game Won");
        gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2
                                   + gameOverText.getGlobalBounds().left,
                               gameOverText.getGlobalBounds().height / 2
                                   + gameOverText.getGlobalBounds().top);
        gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }
}

void
displayMines(int index)
{
    int numberOfMines = expand_button(index);
    if(numberOfMines > 0) {
        buttons[index]->setString(std::to_string(numberOfMines));
    } else {
        buttons[index]->setString("");
    }
    buttons[index]->Enable(false);
    buttons[index]->setTexture(
        sp::ResourceManager::getTexture(RESOURCES_DIR "button_clicked.png"));
}

void
onButtonClick(void* args)
{
    int index = *(static_cast<int*>(args));
    if(flaggedButtons[index])
        return;

    if(!expanded) {
        // If first click, generate minefield and expand the button
        expanded = true;
        int i = 0;
        while(i < remainingMines) {
            int randPos = randInt();
            if(randPos == index || mines[randPos] == -1) {
                continue;
            }
            mines[randPos] = -1;
            i++;
        }
    } else if(mines[index] == -1) {
        // We stepped on a mine, game over
        buttons[index]->setString("B");
        gameOver = true;
        gameOverText.setString("Game Over\nPress Space to restart\n");
        gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2
                                   + gameOverText.getGlobalBounds().left,
                               gameOverText.getGlobalBounds().height / 2
                                   + gameOverText.getGlobalBounds().top);
        gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        return;
    }
    displayMines(index);
}

void
onRightButtonClick(void* args)
{
    int index = *(static_cast<int*>(args));
    auto flagged = flaggedButtons[index];
    flagged = flaggedButtons[index] = !flagged;
    if(remainingMines > 0 && flagged) {
        remainingMines--;
        buttons[index]->setString("F");
    } else if(!flagged) {
        remainingMines++;
        buttons[index]->setString("");
    }
    updateRemainingMinesText();
    if(remainingMines == 0) {
        checkForWinCondition();
    }
}

void
initGame()
{
    expanded = false;
    gameOver = false;
    remainingMines = MAX_MINES;

    expandedButtons.clear();
    flaggedButtons.clear();
    mines.clear();

    expandedButtons = std::vector<bool>(FIELD_WIDTH * FIELD_HEIGHT, false);
    flaggedButtons = std::vector<bool>(FIELD_WIDTH * FIELD_WIDTH, false);
    mines = std::vector<int>(FIELD_WIDTH * FIELD_HEIGHT, 0);

    updateRemainingMinesText();

    auto button = sp::Button(
        sp::ResourceManager::getTexture(RESOURCES_DIR "Button2.png"), "");
    auto sizeX = button.getTextureRect().width;
    auto sizeY = button.getTextureRect().height;
    button.Enable(true);

    for(int i = 0; i < FIELD_WIDTH; i++) {
        for(int j = 0; j < FIELD_HEIGHT; j++) {
            int index = j * FIELD_WIDTH + i;
            buttons[index] = std::unique_ptr<sp::Button>(
                dynamic_cast<sp::Button*>(button.clone()));

            buttons[index]->setPosition(
                sf::Vector2f(sizeX * i + sizeX, sizeY * j + sizeY));
            buttons[index]->SetID(index);
            buttons[index]->onClick(&onButtonClick, &buttons[index]->GetID());
            buttons[index]->onRightClick(&onRightButtonClick);
        }
    }
}

void
updateGame(sf::RenderWindow& window)
{
    if(!gameOver) {
        for(int i = 0; i < buttons.size(); i++) {
            buttons[i]->update(window);
            window.draw(*buttons[i]);
        }
    } else {
        window.draw(gameOverText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
           && window.hasFocus()) {
            initGame();
        }
    }
    window.draw(remainingMinesText);
}