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
class Game {
    GameBoard board_;    ///< 游戏地图
    GameUI ui_;          ///< 控制台 UI 显示工具
    bool gameOver_;      ///< 游戏是否结束
    bool win_;           ///< 是否获胜

    //组长
    void handleInput(const std::string& input); ///< 解析用户输入
    void processReveal(int x, int y);           ///< 处理翻开格子
    void processFlag(int x, int y);             ///< 处理标记格子

public:
    //十七
    Game(int width, int height, int mineCount);

    void run();               ///< 游戏主循环
    static void startMenu(); ///< 静态主菜单入口函数
};

#endif //GAME_H
