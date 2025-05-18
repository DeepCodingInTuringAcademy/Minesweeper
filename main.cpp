#include "include/game.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    Game game(10,10,51);

    while (!game.Begin())game.startMenu();

    while(!game.Over())game.run();

}