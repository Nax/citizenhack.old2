#ifndef MONSTER_H
#define MONSTER_H

#include <vector.h>
#include <monster_data.h>

class Monster
{
public:
    Monster(MonsterID monster_id) : _monster_id(monster_id), _dlevel(0) {}
    ~Monster() {}

    int                 dlevel() const { return _dlevel; }
    MonsterID           monster_id() const { return _monster_id; }
    const MonsterData&  monster_data() const { return MonsterData::from_id(_monster_id); }
    Vector2i            pos() const { return _pos; }

    void    move(int x, int y);
    void    move_relative(int x, int y);
    void    move_dlevel(int dlevel);
    void    move_dlevel_relative(int d);

private:
    MonsterID   _monster_id;
    Vector2i    _pos;
    int         _dlevel;
};

#endif
