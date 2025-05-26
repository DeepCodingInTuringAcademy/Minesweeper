#include "game.h"
#include "utility.h"

int main()
{
    Game game(10, 10, 20);
    game.startMenu();
    if (!game.willExit()) game.run();

    pauseScreen();
    return 0;
}
