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
