#include <game.h>
#include <screen.h>
#include <ctime>
#include <cstdlib>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    srand(time(nullptr));
    Screen screen;
    Game game(screen);

    game.loop();

    return 0;
}
