#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H

#include <wish.h>
#include <monster_id.h>

struct MonsterData
{
    const char*     str;
    wish_unicode    sym;

    static const MonsterData monsters[];

    static const MonsterData& from_id(MonsterID monster)
    {
        return monsters[static_cast<int>(monster)];
    }
};

#endif
