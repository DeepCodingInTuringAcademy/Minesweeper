#include "gameboard.h"

void GameBoard::generateMines(int firstX, int firstY)
{
}

int GameBoard::countAdjacentMines(int x, int y)
{
}

bool GameBoard::inBounds(int x, int y) const
{
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
    if(this->board_[x][y].isRevealed())
    {
        return ;
    }
    this->board_[x][y].reveal();
}

void GameBoard::toggleFlag(int x, int y)
{
    this->board_[x][y].toggleFlag();
}

bool GameBoard::isGameWon() const
{
    for(auto &vecCell : this->board_)
    {
        for(auto cell : vecCell)
        {
            if(cell.isRevealed() && cell.hasMine())
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::isGameOver() const
{
    for(auto &row : this->board_)
    {
        for(auto cell : row)
        {
            if(cell.isRevealed() && cell.hasMine())
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
    if(revealAll)
    {
        for(int i = 0; i < width/2 - 2; i++)
        {
            std::cout << "-";
        }
        std::cout << "Map";
        for(int i = 0; i < width/2 - 2; i++)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
        for(int i = 0; i < width; i++)
        {
            std::cout << "-" << i << "-";
        }
        for(auto &row : this->board_)
        {
            for(auto cell : row)
            {
                if (cell.hasMine())
                {
                    std::cout << " * ";  // 显示地雷
                }
                else
                {
                    std::cout << " " << cell.getAdjacentMines() << " ";  // 显示相邻地雷数
                }
            }
        }
    }
    else
    {
        std::cout << "----------Map---------" << std::endl;
        for(auto &row : this->board_)
        {
            for(auto cell : row)
            {
                if (cell.isRevealed())
                {
                    if (cell.hasMine())
                    {
                        std::cout << " * ";  // 显示地雷
                    }
                    else
                    {
                        std::cout << " " << cell.getAdjacentMines() << " ";  // 显示相邻地雷数
                    }
                }
                else if (cell.isFlagged())
                {
                    std::cout << " F ";  // 显示标记
                }
                else
                {
                    std::cout << " . ";  // 显示未翻开的格子
                }
            }
        }
    }
}

bool GameBoard::cellHasMine(int x, int y) const {
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

bool GameBoard::cellIsFlagged(int x, int y) const {
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

int GameBoard::getWidth() const {
}

int GameBoard::getHeight() const {
}
