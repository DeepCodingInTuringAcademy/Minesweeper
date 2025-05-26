#include "game.h"
#include "utility.h"

int main()
{
    Game game(10, 10, 15);
    while (true) {
        game.startMenu();
        if (!game.willExit()) game.run();
        else break;
    }

    pauseScreen();
    return 0;
}
