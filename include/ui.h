#ifndef UI_H
#define UI_H

/**
 * @file ui.h
 * @brief 定义 GameUI 类，用于控制台界面显示与用户输入。
 */

#pragma once
#include <string>

/**
 * @class GameUI
 * @brief 提供控制台界面交互，显示标题、菜单和提示信息。
 */

//阿浪
class GameUI {
public:
    /// 显示 ASCII 风格游戏标题
    void showTitle() const;

    /// 显示主菜单选项
    void showMainMenu() const;

    /// 显示非法选项提示
    void showInvalidOption() const;

    /// 显示游戏退出信息
    void showExitMessage() const;

    /// 获取用户菜单选择（返回整数）
    [[nodiscard]] int getMenuChoice() const;

    /// 显示输入命令帮助信息
    void showInstructions() const;

    /// 显示命令输入提示符
    void promptInput() const;
};

#endif //UI_H
