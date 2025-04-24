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

// board_ is a 2D array, defined as rows first, then columns
// Check if the cell has a mine
bool GameBoard::cellHasMine(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // Invalid coordinates, return false
    }
    return board_[y][x].hasMine(); // Return if the cell has a mine
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
// Check if the cell is flagged
bool GameBoard::cellIsFlagged(int x, int y) const
{
    if (!inBounds(x, y))
    {
        return false; // Invalid coordinates, return false
    }
    return board_[y][x].isFlagged(); // Return if the cell is flagged
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
// Get the width of the board
int GameBoard::getWidth() const
{
    return width_; // Return the width of the board
}
// Get the height of the board
int GameBoard::getHeight() const
{
    return height_; // Return the height of the board
}
