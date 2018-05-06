#include <ctime>
#include <cstdlib>
#include <hack/screen.h>
#include <hack/game.h>
#include <hack/config.h>
#include <hack/archive.h>
#include <hack/actor_class.h>
#include <hack/actor_data.h>

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
