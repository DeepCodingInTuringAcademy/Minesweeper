#include "ui.h"
#include<iostream>
#include<limits>

void GameUI::showTitle() const {
    std::cout << "  _____  _        _    _  _____  _____  _____  _____  _____  _____  " << std::endl;
    std::cout << " |  _  || |      ||   | ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  | " << std::endl;
    std::cout << " | |_| || |      | |__| || |_| || |_| || |_| || |_| || |_| || |_| | " << std::endl;
    std::cout << " |  ___/| |      |  __  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  | " << std::endl;
    std::cout << " | |    | |____  | |  | || |_| || |_| || |_| || |_| || |_| || |_| | " << std::endl;
    std::cout << " |_|    |______| |_|  |_||_____||_____||_____||_____||_____||_____|\n" << std::endl;
}

void GameUI::showMainMenu() const {
    std::cout << "1. 开始新游戏" << std::endl;
    std::cout << "2. 查看帮助信息" << std::endl;
    std::cout << "3. 退出游戏 " << std::endl;
}

void GameUI::showInvalidOption() const {
    std::cout << "无效选择，请重新输入" << std::endl;
}

void GameUI::showExitMessage() const {
    std::cout << "感谢Play,再会！" << std::endl;
}

int GameUI::getMenuChoice() const {
    int choice;
    while(!(std::cin >> choice)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        showInvalidOption();
    }
    return choice;
}

void GameUI::showInstructions() const {
    std::cout << "扫雷游戏帮助信息：" << std::endl;
    std::cout << "输入坐标来翻开方块，例如 x y" << std::endl;
    std::cout << "目标是翻开所有不是地雷的方块" <<  std::endl;
}

void GameUI::promptInput() const {
    std::cout << "请输入命令：" <<std::endl;
}

void GameUI::printMessage(const std::string &message) const {

}
