#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <hack/dungeon/level.h>
#include <hack/non_copyable.h>

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
