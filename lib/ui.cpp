#include "iostream"
#include "ui.h"
#include "utility.h"


void GameUI::showTitle()
{
    std::cout << R"(   _____  .___ _______  ___________ ___________      _______________________________________________________ )" << std::endl;
    std::cout << R"(  /     \ |   |\      \ \_   _____//   _____/  \    /  \_   _____/\_   _____/\______   \_   _____/\______   \)" << std::endl;
    std::cout << R"( /  \ /  \|   |/   |   \ |    __)_ \_____  \\   \/\/   /|    __)_  |    __)_  |     ___/|    __)_  |       _/)" << std::endl;
    std::cout << R"(/    Y    \   /    |    \|        \/        \\        / |        \ |        \ |    |    |        \ |    |   \)" << std::endl;
    std::cout << R"(\____|__  /___\____|__  /_______  /_______  / \__/\  / /_______  //_______  / |____|   /_______  / |____|_  /)" << std::endl;
    std::cout << R"(        \/            \/        \/        \/       \/          \/         \/                   \/         \/ )" << std::endl;
}

void GameUI::showMainMenu()
{
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Help" << std::endl;
    std::cout << "3. Exit " << std::endl;
}

void GameUI::showInvalidOption()
{
    std::cout << "Invalid option, please enter again!" << std::endl;
}

void GameUI::showExitMessage()
{
    std::cout << "Thanks for play, see you next time!" << std::endl;
}

int GameUI::getMenuChoice()
{
    int choice;
    while (!(std::cin >> choice))
    {
        clearInputBuffer();
        showInvalidOption();
    }
    clearInputBuffer();
    return choice;
}

void GameUI::showInstructions()
{
    std::cout << "Minesweeper Instructions:" << std::endl;
    std::cout << "Enter the command to reveal cells." << std::endl;
    std::cout << "Your goal is to reveal all cells and don't die!" << std::endl;
}

void GameUI::promptInput()
{
    std::cout << "Please enter command:" << std::endl;
}

void GameUI::printMessage(const std::string &message)
{
    std::cout << message << std::endl;
}

void GameUI::printMessage()
{
    printMessage("");
}
