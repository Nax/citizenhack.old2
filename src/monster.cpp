#include <monster.h>

void Monster::move(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

void Monster::move_relative(int x, int y)
{
    _pos.x += x;
    _pos.y += y;
}

void Monster::move_dlevel(int dlevel)
{
    _dlevel = dlevel;
}

void Monster::move_dlevel_relative(int d)
{
    _dlevel += d;
}
