#include <actor.h>

Actor::Actor(ActorID actor_id) : _actor_id(actor_id), _dlevel(0)
{
    //_stats = actor_data().stats;
    _stats = {0};
}

void Actor::move(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

void Actor::move_relative(int x, int y)
{
    _pos.x += x;
    _pos.y += y;
}

void Actor::move_dlevel(int dlevel)
{
    _dlevel = dlevel;
}

void Actor::move_dlevel_relative(int d)
{
    _dlevel += d;
}
