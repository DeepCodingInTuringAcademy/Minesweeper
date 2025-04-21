#include <iostream>
#include "include/cell.h"
#include "include/game.h"
#include "include/gameboard.h"
#include "include/ui.h"
int main() {
    Game game(10,10,100);
    game.startMenu();
    while(game.Over())
    {
        game.run();
    }
}