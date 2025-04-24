#include "cell.h"

Cell::Cell() : hasMine_(false),revealed_(false),flagged_(false),adjacentMines_(0)
{}

/// 设置本格子为地雷
 ///bool hasMine_;        ///< 是否有地雷
  ///  bool revealed_;       ///< 是否已被翻开
  ///  bool flagged_;        ///< 是否被标记
  ///  int adjacentMines_;   ///< 相邻地雷数
void Cell::placeMine()
{
     hasMine_ = true;
}

/// 设置相邻地雷数量
void Cell::setAdjacentMines(int count)
{
    adjacentMines_ = count;
}

/// 判断是否为地雷
bool Cell::hasMine() const
{
    return hasMine_;
}

/// 判断是否已被翻开
bool Cell::isRevealed() const
{
    return revealed_;
}

/// 判断是否被标记
bool Cell::isFlagged() const
{
    return flagged_;
}

/// 获取相邻地雷数量
int Cell::getAdjacentMines() const
{
    return adjacentMines_;
}

/// 翻开格子
void Cell::reveal()
{
    if(!flagged_)
       revealed_ = true;
}

/// 标记或取消标记格子
void Cell::toggleFlag()
{
    if(!flagged_)
        flagged_ = true;
}
