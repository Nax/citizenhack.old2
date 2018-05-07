#ifndef INCLUDED_HACK_DUNGEON_BRANCH_H
#define INCLUDED_HACK_DUNGEON_BRANCH_H

#include <cstdint>

enum class DungeonBranchID : uint8_t
{
    None = 0,
    Dungeon = 1,
    Mines = 2
};

struct DungeonBranch
{
    DungeonBranch(uint8_t id);

    const DungeonBranchData& data() const;

    uint8_t     id;
};

struct DungeonBranchData
{
    const char* name;
};

#endif
