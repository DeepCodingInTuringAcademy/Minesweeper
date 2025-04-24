#include "gameboard.h"
#include <random>
#include <algorithm>

void GameBoard::generateMines(int firstX, int firstY)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::pair<int, int>> allCells;

    // 生成所有可能的格子坐标，排除首次点击的格子
    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            if (x != firstX || y != firstY)
            {
                allCells.emplace_back(x, y);
            }
        }
    }

    // 打乱所有格子坐标
    std::shuffle(allCells.begin(), allCells.end(), gen);

    // 在前 mineCount_ 个格子中放置地雷
    for (int i = 0; i < mineCount_; ++i)
    {
        int x = allCells[i].first;
        int y = allCells[i].second;
        board_[y][x].placeMine();
    }

    // 计算每个格子周围的地雷数
    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            int count = countAdjacentMines(x, y);
            board_[y][x].setAdjacentMines(count);
        }
    }
}

// 计算相邻地雷数
int GameBoard::countAdjacentMines(int x, int y)
{
    int count = 0;
    // 遍历相邻的8个格子
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dx == 0 && dy == 0)
                continue;
            int newX = x + dx;
            int newY = y + dy;
            if (inBounds(newX, newY) && board_[newY][newX].hasMine())
            {
                ++count;
            }
        }
    }
    return count;
}

// 判断坐标是否合法
bool GameBoard::inBounds(int x, int y) const
{
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

GameBoard::GameBoard(int width, int height, int mineCount)
{
}

void GameBoard::revealCell(int x, int y)
{
}

void GameBoard::toggleFlag(int x, int y)
{
}

bool GameBoard::isGameWon() const
{
}

bool GameBoard::isGameOver() const
{
}

void GameBoard::display(bool revealAll) const
{
}

bool GameBoard::cellHasMine(int x, int y) const
{
}

bool GameBoard::cellIsRevealed(int x, int y) const
{
}

bool GameBoard::cellIsFlagged(int x, int y) const
{
}

int GameBoard::getAdjacentMines(int x, int y) const
{
}

int GameBoard::getWidth() const
{
}

int GameBoard::getHeight() const
{
}

GameBoard::GameBoard(int width, int height, int mineCount)
    : width_(width), height_(height), mineCount_(mineCount), firstMove_(true)
{
    board_.resize(height_, std::vector<Cell>(width_));
}
