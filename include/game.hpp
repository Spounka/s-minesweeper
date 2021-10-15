#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include "button.hpp"
#include "config.hpp"
#include "resourcesmanager.hpp"

#include <chrono>
#include <functional>
#include <random>
#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void initGame();
void updateRemainingMinesText();
int expand_button(int index);
void checkForWinCondition();
void displayMines(int index);
void onButtonClick(void* args = nullptr);
void onRightButtonClick(void* args = nullptr);
void updateGame(sf::RenderWindow& window);

#endif