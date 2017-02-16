#include <dungeon_generator_standard.h>

void DungeonGeneratorStandard::make_room(int x, int y, int w, int h)
{
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            if (i == 0 || i == (w - 1) || j == 0 || j == (h - 1))
                _level.set(x + i, y + j, TileID::Wall);
            else
                _level.set(x + i, y + j, TileID::Ground);
        }
    }
}

void DungeonGeneratorStandard::run()
{
    _level.resize(80, 21);
    _level.fill(TileID::Rock);
    make_room(5, 5, 10, 10);
}
