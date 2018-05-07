#ifndef INCLUDED_HACK_DUNGEON_BRANCH_DATA_H
#define INCLUDED_HACK_DUNGEON_BRANCH_DATA_H

#include <cstdint>

enum class DungeonBranchID : uint8_t
{
    None = 0,
    Dungeon = 1,
    Mines = 2
};

struct DungeonBranchData
{
    static size_t                       count();
    static const DungeonBranchData&     from_id(DungeonBranchID);
    const char* name;
};

#endif
