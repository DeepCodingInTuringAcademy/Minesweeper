#include "../include/game.h"
#include "../include/gameboard.h"
#include "../include/ui.h"
#include <iostream>
void Game::handleInput(const std::string &input) {
}

void Game::processReveal(int x, int y) {
}

void Game::processFlag(int x, int y) {
}

Game::Game(int _width, int _height, int _mineCount) {
    board_ = GameBoard(_width,_height,_mineCount);
    ui_ = GameUI();
    gameOver_ = false;
    win_ = false;
}

void Game::run() {
}

void Game::startMenu()
{
}

bool Game::Over()
{
    return gameOver_;
}
