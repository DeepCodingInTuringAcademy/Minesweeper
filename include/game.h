#ifndef GAME_H
#define GAME_H

/**
 * @file game.h
 * @brief 定义 Game 类，控制游戏主循环与流程逻辑。
 */

#pragma once

#include <string>
#include "gameboard.h"
#include "ui.h"

/**
 * @class Game
 * @brief 处理游戏主流程，包括用户输入、游戏更新、菜单入口等。
 */
class Game
{
    GameBoard board_;       ///< 游戏地图
    bool gameOver_ = false; ///< 游戏是否结束
    bool gameExit_ = false; ///< 游戏是否即将退出
    bool win_ = false;      ///< 是否获胜
    bool begin_ = false;    ///< 是否开始游戏
    bool first_ = true;     ///< 是否是第一次输入

    // 组长
    void handleInput(const std::string &input); ///< 解析用户输入
    void processReveal(int x, int y);           ///< 处理翻开格子
    void processFlag(int x, int y);             ///< 处理标记格子
    static std::string usageInfo();

public:
    // 十七
    Game(int, int, int);
    static std::string version();
    void reset();                               /// 重置游戏数据
    [[nodiscard]] bool Over() const;            /// 游戏是否结束
    [[nodiscard]] bool Begin() const;           /// 游戏是否开始
    void run();                                 ///< 游戏主循环
    void startMenu();                           ///< 静态主菜单入口函数
    [[nodiscard]] bool willExit() const;        ///< 游戏是否准备退出
    void exit();                                ///< 游戏准备退出
};

#endif // GAME_H
