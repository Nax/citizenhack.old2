#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <dungeon_level.h>
#include <non_copyable.h>

class Dungeon : public NonCopyable
{
public:
    Dungeon();
    ~Dungeon();

    DungeonLevel&   level(int i);

private:
    std::vector<DungeonLevel>   _levels;
};

#endif
