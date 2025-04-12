#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/**
 * @file gameboard.h
 * @brief 定义扫雷地图 GameBoard 类，包含地图状态和操作逻辑。
 */

#pragma once
#include <vector>
#include "cell.h"

/**
 * @class GameBoard
 * @brief 控制整个扫雷地图，负责地雷布置、翻开逻辑和判定胜负。
 */
class GameBoard {
    int width_;                      ///< 地图宽度
    int height_;                     ///< 地图高度
    int mineCount_;                  ///< 地雷总数
    std::vector<std::vector<Cell>> board_; ///< 地图格子
    bool firstMove_;                 ///< 是否第一次点击（用于避免初点就是雷）

    void generateMines(int firstX, int firstY); ///< 初始化地雷分布
    int countAdjacentMines(int x, int y);       ///< 计算相邻地雷数
    [[nodiscard]] bool inBounds(int x, int y) const;          ///< 判断坐标是否合法

public:
    GameBoard(int width, int height, int mineCount);

    void revealCell(int x, int y);  ///< 翻开格子
    void toggleFlag(int x, int y);  ///< 标记/取消标记格子
    [[nodiscard]] bool isGameWon() const;         ///< 判断是否获胜
    [[nodiscard]] bool isGameOver() const;        ///< 判断是否失败

    void display(bool revealAll = false) const; ///< 显示地图

    // 格子状态访问
    [[nodiscard]] bool cellHasMine(int x, int y) const;
    [[nodiscard]] bool cellIsRevealed(int x, int y) const;
    [[nodiscard]] bool cellIsFlagged(int x, int y) const;
    [[nodiscard]] int getAdjacentMines(int x, int y) const;

    // 地图尺寸
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
};

#endif //GAMEBOARD_H
