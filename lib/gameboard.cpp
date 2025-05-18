#include "../include/gameboard.h"
#include <random>
#include <algorithm>
#include <iostream>
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
    this->width_ = width;
    this->height_ = height;
    this->mineCount_ = mineCount;
    this->firstMove_ = (true);
    this->board_ = std::vector<std::vector<Cell>>(height_, std::vector<Cell>(width_, Cell()));
}

void GameBoard::revealCell(int x, int y)
{
    if (this->board_[x][y].isRevealed())
    {
        return;
    }
    this->board_[x][y].reveal();
}

void GameBoard::toggleFlag(int x, int y)
{
    this->board_[x][y].toggleFlag();
}

bool GameBoard::isGameWon() const
{
    for (auto &vecCell : this->board_)
    {
        for (auto cell : vecCell)
        {
            if (cell.isRevealed() && cell.hasMine())
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::isGameOver() const
{
    for (auto &row : this->board_)
    {
        for (auto cell : row)
        {
            if (cell.isRevealed() && cell.hasMine())
            {
                return true;
            }
        }
    }
    return false;
}

void GameBoard::display(bool revealAll) const
{
    int height = this->getHeight();
    int width = this->getWidth();
    if (revealAll)
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << " ";
        }
        std::cout << "Map" << std::endl;
        for (int i = 0; i < width; i++)
        {
            std::cout << "-" << i << "-";
        }
        std::cout << std::endl;
        for (auto &row : this->board_)
        {
            for (auto cell : row)
            {
                if (cell.hasMine())
                {
                    std::cout << " * "; // 显示地雷
                }
                else
                {
                    std::cout << " " << cell.getAdjacentMines() << " "; // 显示相邻地雷数
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << " ";
        }
        std::cout << "Map" << std::endl;
        for (int i = 0; i < width; i++)
        {
            std::cout << "-" << i << "-";
        }
        std::cout << std::endl;
        for (auto &row : this->board_)
        {
            for (auto cell : row)
            {
                if (cell.isRevealed())
                {
                    if (cell.hasMine())
                    {
                        std::cout << " * "; // 显示地雷
                    }
                    else
                    {
                        std::cout << " " << cell.getAdjacentMines() << " "; // 显示相邻地雷数
                    }
                }
                else if (cell.isFlagged())
                {
                    std::cout << " F "; // 显示标记
                }
                else
                {
                    std::cout << " . "; // 显示未翻开的格子
                }
            }
            std::cout << std::endl;
        }
    }
}

bool GameBoard::cellHasMine(int x, int y) const
{
    return false;
}
// Check if the cell is revealed
bool GameBoard::cellIsRevealed(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // Invalid coordinates, return false
    }
    return board_[y][x].isRevealed(); // Return if the cell is revealed
}

bool GameBoard::cellIsFlagged(int x, int y) const
{
    return false;
}
// Get the number of adjacent mines to the cell
int GameBoard::getAdjacentMines(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return -1; // Invalid coordinates, return -1
    }
    return board_[y][x].getAdjacentMines(); // Return the number of adjacent mines
}

int GameBoard::getWidth() const
{
    return this->width_;
}

int GameBoard::getHeight() const
{
    return this->height_;
}
