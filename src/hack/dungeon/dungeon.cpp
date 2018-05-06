#include <hack/dungeon/dungeon.h>
#include <hack/dungeon_generator_standard.h>

Dungeon::Dungeon()
{
    _levels.resize(40);
}

Dungeon::~Dungeon()
{

}

DungeonLevel& Dungeon::level(int i)
{
    DungeonLevel& level = _levels[i];

    if (level.empty())
        DungeonGeneratorStandard::generate(level);
    return level;
}
