#ifndef ACTION_MOVE_H
#define ACTION_MOVE_H

#include <action.h>
#include <dungeon_level.h>
#include <actor.h>

class ActionMove : public Action
{
public:
    ActionMove(DungeonLevel& level, Actor& actor, Vector2i delta);
    int    perform() override;

private:
    DungeonLevel&   _level;
    Actor&        _actor;
    Vector2i        _delta;
};

#endif
