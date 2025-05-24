#include "gameboard.h"

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

  // 打印列号
  std::cout << "    "; // 行号空白占位
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
      const auto &cell = this->board_[row][col];

      if (revealAll || cell.isRevealed())
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

bool GameBoard::cellHasMine(int x, int y) const
{
  if (!inBounds(x, y))
  {
    return false; // Invalid coordinates, return false
  }
  return board_[x][y].hasMine();
}
// Check if the cell is revealed
bool GameBoard::cellIsRevealed(int x, int y) const
{
  if (!inBounds(x, y))
  {
    return false; // Invalid coordinates, return false
  }
  return board_[x][y].isRevealed(); // Return if the cell is revealed
}

bool GameBoard::cellIsFlagged(int x, int y) const
{
  if (!inBounds(x, y))
  {
    return false; // Invalid coordinates, return false
  }
  return board_[x][y].isFlagged();
}
// Get the number of adjacent mines to the cell
int GameBoard::getAdjacentMines(int x, int y) const
{
  if (!inBounds(x, y))
  {
    return -1; // Invalid coordinates, return -1
  }
  return board_[x][y].getAdjacentMines(); // Return the number of adjacent mines
}

int GameBoard::getWidth() const
{
  return this->width_;
}

int GameBoard::getHeight() const
{
  return this->height_;
}
