#include <game.h>
#include <screen.h>
#include <ctime>
#include <cstdlib>
#include <config.h>
#include <archive.h>
#include <actor_class.h>
#include <actor_data.h>

static void load_game_data()
{
    Archive archive;

    archive.open(DATA_DIR "/data.bin");
    ActorClass::load(archive);
    ActorData::load(archive);
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    load_game_data();

    srand(time(nullptr));
    Screen screen;
    Game game(screen);

    game.loop();

    return 0;
}
