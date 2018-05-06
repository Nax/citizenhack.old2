#include <hack/actor.h>

Actor::Actor(ActorID actor_id)
: _actor_id(actor_id)
, _ct(0)
, _dlevel(0)
{
    //_stats = actor_data().stats;
    _stats = Stats{};
    _stats.speed = 10;
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

bool Actor::ct_check()
{
    _ct += _stats.speed;
    if (_ct >= 100)
    {
        _ct -= 100;
        return true;
    }
    return false;
}
