#ifndef ACTION_MOVE_H
#define ACTION_MOVE_H

#include <hack/action.h>
#include <hack/dungeon/level.h>
#include <hack/actor.h>

class ActionMove : public Action
{
public:
    ActionMove(DungeonLevel& level, Actor& actor, Vector2i delta);
    int    perform() override;

private:
    DungeonLevel&   _level;
    Actor&          _actor;
    Vector2i        _delta;
};

#endif
