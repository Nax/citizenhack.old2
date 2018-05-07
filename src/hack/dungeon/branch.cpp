#include <hack/dungeon/branch.h>

static const DungeonBranchData data[] = {
    {""},
    {"The Dungeons of Doom"},
    {"The Mythril Mines"}
};

DungeonBranch::DungeonBranch()
: id(0)
{

}


const DungeonBranchData& DungeonBranch::data() const
{
    return data[id];
}
