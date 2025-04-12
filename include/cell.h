#ifndef CELL_H
#define CELL_H

/**
 * @file cell.h
 * @brief 定义单个格子的 Cell 类，用于表示地图中的一个单位格。
 */

#pragma once

/**
 * @class Cell
 * @brief 表示扫雷地图中的一个格子，包含地雷、翻开、标记等信息。
 */
class Cell {
    bool hasMine_;        ///< 是否有地雷
    bool revealed_;       ///< 是否已被翻开
    bool flagged_;        ///< 是否被标记
    int adjacentMines_;   ///< 相邻地雷数

public:
    Cell();

    /// 设置本格子为地雷
    void placeMine();

    /// 设置相邻地雷数量
    void setAdjacentMines(int count);

    /// 判断是否为地雷
    [[nodiscard]] bool hasMine() const;

    /// 判断是否已被翻开
    [[nodiscard]] bool isRevealed() const;

    /// 判断是否被标记
    [[nodiscard]] bool isFlagged() const;

    /// 获取相邻地雷数量
    [[nodiscard]] int getAdjacentMines() const;

    /// 翻开格子
    void reveal();

    /// 标记或取消标记格子
    void toggleFlag();
};

#endif //CELL_H
