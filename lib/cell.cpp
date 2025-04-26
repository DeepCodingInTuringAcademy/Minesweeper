#include "cell.h"
#include "cstring"
#include "cstdlib"
#include "ctime"
Cell::Cell() : hasMine_(false),revealed_(false),flagged_(false),adjacentMine_(0)
{
}

/// 设置本格子为地雷

 ///bool hasMine_;        ///< 是否有地雷
  ///  bool revealed_;       ///< 是否已被翻开
  ///  bool flagged_;        ///< 是否被标记
  ///  int adjacentMines_;   ///< 相邻地雷数
void Cell::placeMine()
{
     //设置随机数种子
     srand(time(NULL));
     //随机设置十个雷  用1表示
     for(int i=0;i<10;)
     {
         //数组的有效下标【0，9】
         int x = rand()%10;
         int y = rand()%10;
         if(map[x][y]==false)
            {
               map[x][y] = true;
               hasMine_ = true;
               i++;
            }
}

/// 设置相邻地雷数量
void Cell::setAdjacentMines(int count)
{
     for(int i=0;i<10;i++)
     {
         for(int j=0;j<10;j++)
         {
             if(map[i][j]==true&&(map[i+1][j]==true||map[i-1][j]==true||map[i][j+1]==true||map[i][j-1]==true))
             {
                  count++;
             }
         }
     }
    adjacentMines = count;///< 相邻地雷数
}

/// 判断是否为地雷
bool Cell::hasMine() const
{
     if(int i=0;i<10;i++)
     {
         for(int j=0;j<10;j++)
         {
              if(map[i][j]==true)
                  return true;
              else
                  return false;
         }
     }
}

/// 判断是否已被翻开
bool Cell::isRevealed() const
{
    if(revealCell(x,y))///< 翻开格子
       revealed_=true;///已被翻开
    else
       revealed_=false;
    return revealed_;
///bool hasMine_;        ///< 是否有地雷
  ///  bool revealed_;       ///< 是否已被翻开
  ///  bool flagged_;        ///< 是否被标记
  ///  int adjacentMines_;   ///< 相邻地雷数
}

/// 判断是否被标记
bool Cell::isFlagged() const
{
    if(toggleFlag(x,y)==true)///< 标记/取消标记格子
        flagged_=true;///< 被标记
    else
        flagged_=false;///没被标记
    return flagged_;
}

/// 获取相邻地雷数量
int Cell::getAdjacentMines() const
{
    return adjacentMines;
}

/// 翻开格子
void Cell::reveal()
{
    if(!flagged_)
       revealed_ = true;
    else
       revealed_ = false;
}

/// 标记或取消标记格子
void Cell::toggleFlag()
{
    if(!flagged_)
       flagged_ = !flagged_;
}
