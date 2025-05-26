
#include "game.h"
#include "utility.h"
#include "iostream"


void Game::handleInput(const std::string &input)
{
    const std::vector<std::string> ipt_vec = split(input);

    if (ipt_vec.empty())
    {
        throw std::invalid_argument(
            "You didn't enter an instruction!");
    }

    if (ipt_vec.size() != 3)
    {
        throw std::invalid_argument(
            "Invalid command format!");
    }

    const std::string &command = ipt_vec[0];

    if (command != "reveal" && command != "r" && command != "flag" && command != "f")
    {
        throw std::invalid_argument(
            "Unknown command \"" + command + "\"!");
    }

    int cur_x, cur_y;
    try
    {
        cur_x = std::stoi(ipt_vec[1]);
        cur_y = std::stoi(ipt_vec[2]);
    }
    catch (const std::invalid_argument &)
    {
        throw std::invalid_argument(
            "Coordinates must be integers!");
    }

    if (command == "reveal" || command == "r")
    {
        if (first_)
        {
            board_.generateMines(cur_x, cur_y); // 埋雷
            first_ = false;
        }
        processReveal(cur_x, cur_y);
    }
    else if (command == "flag" || command == "f")
    {
        processFlag(cur_x, cur_y);
    }
}

void Game::processReveal(int x, int y)
{
    if (board_.cellIsRevealed(x, y))
    {
        ui_.printMessage("This cell is already revealed.");
        return;
    }

    if (board_.cellIsFlagged(x, y))
    {
        ui_.printMessage("This cell is flagged. Remove flag first.");
        return;
    }

    board_.revealCell(x, y);

    if (board_.isGameOver())
    {
        gameOver_ = true;
        return;
    }

    if (board_.isGameWon())
    {
        gameOver_ = true;
        win_ = true;
    }
}

void Game::processFlag(int x, int y)
{
    if (board_.cellIsRevealed(x, y))
    {
        ui_.printMessage("You can't flag a revealed cell.");
        return;
    }

    board_.toggleFlag(x, y);
    board_.display();
}

Game::Game(const int width, const int height, const int mineCount) : board_(width, height, mineCount)
{
    ui_ = GameUI();
    gameOver_ = false;
    win_ = false;
    begin_ = false;
    first_ = true;
}

void Game::run()
{
    std::string error;
    while (!this->Over()) {
        clearScreen();
        board_.display();  // 显示当前地图状态

        if (!error.empty()) {
            GameUI::printMessage(error); // 如果有错误，打印错误信息
            GameUI::printMessage(usageInfo());
            error.clear();
        }
        GameUI::promptInput(); // 提示用户输入

        std::string input;
        std::getline(std::cin, input); // 获取用户输入

        try
        {
            handleInput(input); // 处理输入
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
        }

        clearScreen();
        board_.display();
    }

    pauseScreen();
    clearScreen();
    if (gameOver_)
    { // 游戏结束检查
        if (win_)
        {
            ui_.printMessage("Congratulations! You won!");
        }
        else
        {
            ui_.printMessage("Game Over! You hit a mine.");
        }
        board_.display(true); // 显示完整地图
    }
    else
    {
        board_.display(); // 显示当前地图状态
    }
}

void Game::startMenu()
{
    ui_.showTitle();
    ui_.showMainMenu();
    switch (ui_.getMenuChoice())
    {
    case 1:
        begin_ = true;
        break;
    case 2:
        ui_.showInstructions();
        break;
    case 3:
        ui_.showExitMessage();
        exit(0);
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

bool Game::Begin() const
{
    return begin_;
}

std::string Game::usageInfo()
{
    return "Usage:\n"
           "  reveal/r <x> <y> or r <x> <y>    - Reveal the cell at (x, y)\n"
           "  flag/f <x> <y> or f <x> <y>      - Place or remove a flag at (x, y)";
}
