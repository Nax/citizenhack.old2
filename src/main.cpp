#include <game.h>
#include <screen.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    Screen screen;
    Game game(screen);

    game.loop();

    return 0;
}
