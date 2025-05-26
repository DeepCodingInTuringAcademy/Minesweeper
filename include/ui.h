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

// 阿浪
class GameUI
{
public:
    /// 显示 ASCII 风格游戏标题
    static void showTitle() ;

    /// 显示主菜单选项
    static void showMainMenu() ;

    /// 显示非法选项提示
    static void showInvalidOption() ;

    /// 显示游戏退出信息
    static void showExitMessage() ;

    /// 获取用户菜单选择（返回整数）
    [[nodiscard]] static int getMenuChoice() ;

    /// 显示输入命令帮助信息
    static void showInstructions() ;

    /// 显示命令输入提示符
    static void promptInput() ;

    /// 打印提示信息（如错误、成功、操作反馈）
    static void printMessage(const std::string &message) ;

    static void printMessage();
};

#endif // UI_H
