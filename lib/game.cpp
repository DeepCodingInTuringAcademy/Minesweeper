
#include "game.h"
#include "gameboard.h"
#include "ui.h"
#include "utility.h"
#include <iostream>
#include <stdexcept>

void Game::handleInput(const std::string &input) {
    std::vector<std::string> ipt_vec = split(input);

    if (ipt_vec.empty()) {
        throw std::invalid_argument(
                "You didn't enter an instruction!\n" + usageInfo()
        );
    }

    if (ipt_vec.size() != 3) {
        throw std::invalid_argument(
                "Invalid command format!\n" + usageInfo()
        );
    }

    const std::string& command = ipt_vec[0];

    if (command != "reveal" && command != "r" && command != "flag" && command != "f") {
        throw std::invalid_argument(
                "Unknown command \"" + command + "\"!\n" + usageInfo()
        );
    }

    int cur_x, cur_y;
    try {
        cur_x = std::stoi(ipt_vec[1]);
        cur_y = std::stoi(ipt_vec[2]);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument(
                "Coordinates must be integers!\n" + usageInfo()
        );
    }

    if (command == "reveal" || command == "r") {
        processReveal(cur_x, cur_y);
    } else if (command == "flag" || command == "f") {
        processFlag(cur_x, cur_y);
    }
}


void Game::processReveal(int x, int y) {
    if (board_.cellIsRevealed(x, y)) {
        ui_.printMessage("This cell is already revealed.");
        return;
    }

    if (board_.cellIsFlagged(x, y)) {
        ui_.printMessage("This cell is flagged. Remove flag first.");
        return;
    }

    // inBounds在Gameboard中是私有方法，要求在Gameboard中遇到超界参数时抛出std::invalid_argument
    try {
        board_.revealCell(x, y);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument(
                "Coordinates out of bounds!\n"
                "  <x> must be in range [0, " + std::to_string(board_.getWidth()) + ")\n"
                "  <y> must be in range [0, " + std::to_string(board_.getHeight()) + ")\n" +
                usageInfo()
        );
    }
    
    if (board_.isGameOver()) {
        gameOver_ = true;
        board_.display(true);
        ui_.printMessage("Game Over! You hit a mine.");
        return;
    }

    if (board_.isGameWon()) {
        gameOver_ = true;
        win_ = true;
        board_.display(true);
        ui_.printMessage("Congratulations! You win!");
        return;
    }

    board_.display();
}

void Game::processFlag(int x, int y) {
    if (board_.cellIsRevealed(x, y)) {
        ui_.printMessage("You can't flag a revealed cell.");
        return;
    }

    // inBounds在Gameboard中是私有方法，要求在Gameboard中遇到超界参数时抛出std::invalid_argument
    try {
        board_.toggleFlag(x, y);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument(
                "Coordinates out of bounds!\n"
                "  <x> must be in range [0, " + std::to_string(board_.getWidth()) + ")\n"
                                                                                    "  <y> must be in range [0, " + std::to_string(board_.getHeight()) + ")\n" +
                usageInfo()
        );
    }

    board_.display();
}

Game::Game(int width, int height, int mineCount) : board_(width, height, mineCount) {
    ui_ = GameUI();
    gameOver_ = false;
    win_ = false;
}

void Game::run() {
    ui_.promptInput();  // 提示用户输入
    std::string input;
    std::getline(std::cin, input);  // 获取用户输入

    try {
        handleInput(input);  // 处理输入
    } catch (const std::invalid_argument& e) {
        ui_.printMessage(e.what());  // 如果有错误，打印错误信息
        return;
    }

    if (gameOver_) {  // 游戏结束检查
        if (win_) {
            ui_.printMessage("Congratulations! You won!");
        } else {
            ui_.printMessage("Game Over! You hit a mine.");
        }
        board_.display(true);  // 显示完整地图
    } else {
        board_.display();  // 显示当前地图状态
    }
}

void Game::startMenu()
{
    ui_.showTitle();
    ui_.showMainMenu();
    switch (ui_.getMenuChoice()) {
        case 1:
            break;
        case 2:
            ui_.showInstructions();
            break;
        case 3:
            ui_.showExitMessage();
            break;
        default:
            ui_.showInvalidOption();
            break;
    }
}

bool Game::Over() const
{
    return gameOver_;
}

std::string Game::usageInfo() {
    return "Usage:\n"
    "  reveal/r <x> <y> or r <x> <y>    - Reveal the cell at (x, y)\n"
    "  flag/f <x> <y> or f <x> <y>      - Place or remove a flag at (x, y)";
}
