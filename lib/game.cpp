#include "game.h"
#include <vector>
#include "utility.h"
#include "iostream"
#include "soundPlay.h"


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
    if (!board_.inBounds(cur_x, cur_y)) {
        throw std::invalid_argument(
        "Coordinates out of bounds!\n"
        "  <x> must be in range [0, " +
        std::to_string(board_.getWidth()) + ")\n"
                                            "  <y> must be in range [0, " +
        std::to_string(board_.getHeight()) + ")\n");
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

void Game::processReveal(const int x, const int y) {
    if (board_.cellIsRevealed(x, y)) {
        GameUI::printMessage("This cell is already revealed.");
        return;
    }

    if (board_.cellIsFlagged(x, y)) {
        GameUI::printMessage("This cell is flagged. Remove flag first.");
        return;
    }

    // 提前掀开当前格子（无论是否有雷或数字）
    board_.revealCell(x, y);

    // 如果点到雷，游戏结束
    if (board_.cellHasMine(x, y)) {
        gameOver_ = true;
        return;
    }

    // 如果是数字格子（周围有雷），不扩展
    if (board_.cellHasAdjacentMines(x, y)) {
        return;
    }

    // BFS 处理空白区域
    std::vector<std::pair<int, int>> queue;
    queue.emplace_back(x, y);

    while (!queue.empty()) {
        const auto [current_x, current_y] = queue.front();
        queue.erase(queue.begin());

        // 检查 8 个方向的相邻格子
        for (int i = current_x - 1; i <= current_x + 1; ++i) {
            if (!board_.inBoundsX(i)) continue;

            for (int j = current_y - 1; j <= current_y + 1; ++j) {
                if (!board_.inBoundsY(j)) continue;
                if (i == current_x && j == current_y) continue; // 跳过自身

                if (!board_.cellIsRevealed(i, j) && !board_.cellIsFlagged(i, j)) {
                    board_.revealCell(i, j); // 先掀开格子

                    // 如果是空白格子，加入队列继续扩展
                    if (!board_.cellHasAdjacentMines(i, j) && !board_.cellHasMine(i, j)) {
                        queue.emplace_back(i, j);
                    }
                }
            }
        }
    }
}

void Game::processFlag(const int x, const int y)
{
    if (board_.cellIsRevealed(x, y))
    {
        GameUI::printMessage("You can't flag a revealed cell.");
        return;
    }

    board_.toggleFlag(x, y);
    board_.display();
}

Game::Game(const int width, const int height, const int mineCount) : board_(width, height, mineCount)
{
    gameOver_ = false;
    win_ = false;
    begin_ = false;
    first_ = true;
}

std::string Game::version()
{
    return "v 1.0.0";
}

void Game::reset()
{
    board_ = {board_.getWidth(), board_.getHeight(), board_.getMineCount()};
    gameOver_ = false;
    win_ = false;
    begin_ = false;
    first_ = true;
}

void Game::run()
{
    reset();
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
        updateStatus();
    }

    clearScreen();
    main_music.stop();
    board_.display(true); // 显示完整地图
    if (win_) {
        GameUI::printMessage("Congratulations! You won!");
        win_music.play();
    }
    else {
        GameUI::printMessage("Game Over! You hit a mine.");
        lose_music.play();
    }
    GameUI::printMessage("Enter any key to return main menu...");
    while (!std::cin.get()) {}
    begin_ = false;
}

void Game::updateStatus() {
    if (board_.isGameLose()) {
        gameOver_ = true;
    } else if (board_.isGameWon()) {
        gameOver_ = true;
        win_ = true;
    }
}

void Game::startMenu()
{
    main_music.play();
    main_music.setLooping(true);
    while (!Begin()) {
        clearScreen();
        GameUI::showTitle();
        GameUI::showMainMenu();
        switch (GameUI::getMenuChoice())
        {
        case 1:
            begin_ = true;
            break;
        case 2:
            while (true) {
                clearScreen();
                GameUI::showTitle();
                GameUI::showInstructions();
                GameUI::printMessage(usageInfo());
                GameUI::printMessage();
                GameUI::printMessage("Enter any key to return main menu...");
                if (std::cin.get()) {
                    break;
                }
            }
            break;
        case 3:
            clearScreen();
            GameUI::showTitle();
            GameUI::showExitMessage();
            exit();
            return;
        default:
            GameUI::showInvalidOption();
            break;
        }
    }

}

bool Game::willExit() const
{
    return gameExit_;
}

void Game::exit()
{
    gameExit_ = true;
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
           "  [reveal/r] <x> <y>    - Reveal the cell at (x, y)\n"
           "  [flag/f] <x> <y>      - Place or remove a flag at (x, y)";
}
