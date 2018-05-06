#ifndef INCLUDED_HACK_DUNGEON_ROOM_H
#define INCLUDED_HACK_DUNGEON_ROOM_H

#include <hack/math/rect.h>

struct DungeonRoom
{
    Rect2i  pos;
    bool    lit;
};

#endif
