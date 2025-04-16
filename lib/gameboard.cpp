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

// board_是二维数组，先定义行，再定义列
// 判断格子是否有地雷
bool GameBoard::cellHasMine(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // 坐标不合法，返回 false
    }
    return board_[y][x].hasMine(); // 返回格子是否有地雷
}
// 判断格子是否被揭开
bool GameBoard::cellIsRevealed(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // 坐标不合法，返回 false
    }
    return board_[y][x].isRevealed(); // 返回格子是否被揭开
}
// 判断格子是否被标记
bool GameBoard::cellIsFlagged(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // 坐标不合法，返回 false
    }
    return board_[y][x].isFlagged(); // 返回格子是否被标记
}
// 获取格子周围地雷数
int GameBoard::getAdjacentMines(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return -1; // 坐标不合法，返回 -1
    }
    return board_[y][x].getAdjacentMines(); // 返回格子周围地雷数
}
// 获取地图宽度
int GameBoard::getWidth() const
{
    return width_; // 返回地图宽度
}
// 获取地图高度
int GameBoard::getHeight() const
{
    return height_; // 返回地图高度
}
