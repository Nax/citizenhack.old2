#ifndef DUNGEON_GENERATOR_STANDARD_H
#define DUNGEON_GENERATOR_STANDARD_H

#include <dungeon_level.h>

class DungeonGeneratorStandard
{
public:
    DungeonGeneratorStandard(DungeonLevel& level) : _level(level) {}
    ~DungeonGeneratorStandard() {}

    void run();
    void make_room(int x, int y, int w, int h);

    static void generate(DungeonLevel& level)
    {
        DungeonGeneratorStandard gen(level);
        gen.run();
    }

private:
    DungeonLevel& _level;
};

#endif
