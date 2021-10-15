#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include "config.hpp"
#include "resourcesmanager.hpp"

#include <button.hpp>
#include <chrono>
#include <functional>
#include <random>
#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 10;
const int MAX_MINES = 20;
int remainingMines = MAX_MINES;
sf::Text remainingMinesText
    = sf::Text("Remaining mines: ",
               sp::ResourceManager::getFont(RESOURCES_DIR "FreeMono.otf"));

uint seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
std::uniform_int_distribution<int> distribution(0, FIELD_WIDTH* FIELD_HEIGHT);
auto randInt = std::bind(distribution, generator);

std::vector<std::unique_ptr<sp::Button>> buttons(FIELD_WIDTH* FIELD_HEIGHT);
std::vector<int> mines(FIELD_WIDTH* FIELD_HEIGHT, 0);
std::vector<bool> expandedButtons(FIELD_WIDTH* FIELD_HEIGHT, false);
std::vector<bool> flaggedButtons(FIELD_WIDTH* FIELD_WIDTH, false);

auto expanded = false;
auto gameOver = false;
auto gameWon = false;

void initGame();
void updateRemainingMinesText();
int expand_button(int index);
void checkForWinCondition();
void displayMines(int index);
void onButtonClick(void* args = nullptr);
void onRightButtonClick(void* args = nullptr);

#endif