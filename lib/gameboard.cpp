#include "gameboard.h"
#include <algorithm>
#include <iomanip>
#include "iostream"
#include "random"


void GameBoard::generateMines(const int firstX, const int firstY)
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
  std::ranges::shuffle(allCells, gen);

  // 在前 mineCount_ 个格子中放置地雷
  for (int i = 0; i < mineCount_; ++i)
  {
    const int x = allCells[i].first;
    const int y = allCells[i].second;
    board_[y][x].placeMine();
  }

  // 计算每个格子周围的地雷数
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      const int count = countAdjacentMines(x, y);
      board_[y][x].setAdjacentMines(count);
    }
  }
}

// 计算相邻地雷数
int GameBoard::countAdjacentMines(const int x, const int y) const
{
  int count = 0;
  // 遍历相邻的8个格子
  for (int dy = -1; dy <= 1; ++dy)
  {
    for (int dx = -1; dx <= 1; ++dx)
    {
      if (dx == 0 && dy == 0)
        continue;
      const int newX = x + dx;
      if (const int newY = y + dy; inBounds(newX, newY) && board_[newY][newX].hasMine())
      {
        ++count;
      }
    }
  }
  return count;
}

bool GameBoard::inBoundsX(const int x) const
{
  return x >= 0 && x < width_;
}

bool GameBoard::inBoundsY(const int y) const
{
  return y >= 0 && y < height_;
}

// 判断坐标是否合法
bool GameBoard::inBounds(const int x, const int y) const
{
  return inBoundsX(x) && inBoundsY(y);
}

GameBoard::GameBoard(const int width, const int height, const int mineCount)
{
  this->width_ = width;
  this->height_ = height;
  this->mineCount_ = mineCount;
  this->board_ = std::vector(height_, std::vector(width_, Cell()));
}

void GameBoard::revealCell(const int x, const int y)
{
  if (this->board_[x][y].isRevealed())
  {
    return;
  }
  this->board_[x][y].reveal();
}

void GameBoard::toggleFlag(const int x, const int y)
{
  this->board_[x][y].toggleFlag();
}

bool GameBoard::isGameWon() const
{
  for (const auto &row : board_)
  {
    for (const auto &cell : row)
    {
      if (!cell.hasMine() && !cell.isRevealed())
      {
        return false; // 非地雷格子没翻开，未胜利
      }
    }
  }
  return true; // 所有非雷格子都翻开了，胜利
}

bool GameBoard::isGameLose() const
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

void GameBoard::display(const bool revealAll) const
{
  const int height = this->getHeight();
  const int width = this->getWidth();

  // 打印列号
  std::cout << "   "; // 行号空白占位
  for (int col = 0; col < width; ++col)
  {
    std::cout << std::setw(3) << col;
  }
  std::cout << std::endl;

  std::cout << "   +";
  for (int col = 0; col < width; ++col)
  {
    std::cout << "---";
  }
  std::cout << "+" << std::endl;

  for (int row = 0; row < height; ++row)
  {
    std::cout << std::setw(3) << row << "|";
    for (int col = 0; col < width; ++col)
    {
      if (const auto &cell = this->board_[row][col]; revealAll || cell.isRevealed())
      {
        if (cell.hasMine())
        {
          std::cout << " * ";
        }
        else
        {
          std::cout << " " << cell.getAdjacentMines() << " ";
        }
      }
      else if (cell.isFlagged())
      {
        std::cout << " F ";
      }
      else
      {
        std::cout << " . ";
      }
    }
    std::cout << "|" << std::endl;
  }

  std::cout << "   +";
  for (int col = 0; col < width; ++col)
  {
    std::cout << "---";
  }
  std::cout << "+" << std::endl;
}

bool GameBoard::cellHasMine(const int x, const int y) const
{
  return board_[x][y].hasMine();
}

bool GameBoard::cellHasAdjacentMines(const int x, const int y) const
{
  return board_[x][y].hasAdjacentMines();
}

// Check if the cell is revealed
bool GameBoard::cellIsRevealed(const int x, const int y) const
{
  return board_[x][y].isRevealed(); // Return if the cell is revealed
}

bool GameBoard::cellIsFlagged(const int x, const int y) const
{
  return board_[x][y].isFlagged();
}

int GameBoard::getWidth() const
{
  return this->width_;
}

int GameBoard::getHeight() const
{
  return this->height_;
}

int GameBoard::getMineCount() const
{
  return this->mineCount_;
}
