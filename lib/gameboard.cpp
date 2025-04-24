/#include "gameboard.h"

    void GameBoard::generateMines(int firstX, int firstY) {
}

int GameBoard::countAdjacentMines(int x, int y) {
}

bool GameBoard::inBounds(int x, int y) const {
}

GameBoard::GameBoard(int width, int height, int mineCount) {
}

void GameBoard::revealCell(int x, int y) {
}

void GameBoard::toggleFlag(int x, int y) {
}

bool GameBoard::isGameWon() const {
}

bool GameBoard::isGameOver() const {
}

void GameBoard::display(bool revealAll) const {
}

bool GameBoard::cellHasMine(int x, int y) const {
}

bool GameBoard::cellIsRevealed(int x, int y) const {
}

bool GameBoard::cellIsFlagged(int x, int y) const {
}

int GameBoard::getAdjacentMines(int x, int y) const {
}

int GameBoard::getWidth() const {
}

int GameBoard::getHeight() const {
}
