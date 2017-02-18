#ifndef DUNGEON_GENERATOR_STANDARD_H
#define DUNGEON_GENERATOR_STANDARD_H

#include <vector>
#include <dungeon_level.h>
#include <rect.h>

class DungeonGeneratorStandard
{
public:
    DungeonGeneratorStandard(DungeonLevel& level) : _level(level) {}
    ~DungeonGeneratorStandard() {}

    Vector2i    room_door(Rect2i room);
    Vector2i    room_rand_wall(Rect2i room);
    void        make_path(Vector2i src, Vector2i dst);
    void        link_rooms(Rect2i room1, Rect2i room2);
    void        link_all_rooms();
    void        run();
    void        make_rooms();
    bool        try_make_room(Rect2i room);
    void        make_room(Rect2i room);

    static void generate(DungeonLevel& level)
    {
        DungeonGeneratorStandard gen(level);
        gen.run();
    }

private:
    DungeonLevel&           _level;
    std::vector<Rect2i>     _rooms;
};

#endif
