#ifndef MONSTER_H
#define MONSTER_H

#include <vector.h>
#include <monster_data.h>

class Monster
{
public:
    Monster(MonsterID monster_id) : _monster_id(monster_id) {}
    ~Monster() {}

    MonsterID           monster_id() const { return _monster_id; }
    const MonsterData&  monster_data() const { return MonsterData::from_id(_monster_id); }
    Vector2i            pos() const { return _pos; }

    void    move(int x, int y);
    void    move_relative(int x, int y);

private:
    MonsterID   _monster_id;
    Vector2i    _pos;
};

#endif
