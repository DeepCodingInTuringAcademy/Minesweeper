#include <iostream>
#include "include/cell.h"
#include "include/game.h"
#include "include/gameboard.h"
#include "include/ui.h"
#include <windows.h>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Game game(10,10,100);
    game.startMenu();
    while(game.Over())
    {
        game.run();
    }
}