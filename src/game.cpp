#include "game.hpp"
#include "config.hpp"
#include "resourcesmanager.hpp"
#include <iostream>

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
    int x = index % FIELD_WIDTH;
    int y = index / FIELD_HEIGHT;

    for(int i = -1; i < 2; i++) {
        bool yWithinBounds = (y + i >= 0) && (y + i < FIELD_HEIGHT);
        for(int j = -1; j < 2; j++) {
            bool xWithinBounds = (x + j >= 0) && (x + j < FIELD_WIDTH);
            int neighbourMine = (y + i) * FIELD_WIDTH + (x + j);
            if(xWithinBounds && yWithinBounds) {
                if(mines[neighbourMine] == -1 && neighbourMine != index) {
                    numberOfMines++;
                } else if(neighbourMine != index)
                    displayMines(neighbourMine);
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
        buttons[index]->setString("B");
        gameOver = true;
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
            buttons[index]->onClick(&onButtonClick, &buttons[index]->getID());
            buttons[index]->onRightClick(&onRightButtonClick);
        }
    }
}