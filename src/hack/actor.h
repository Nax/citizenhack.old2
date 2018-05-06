#ifndef ACTOR_H
#define ACTOR_H

#include <hack/vector.h>
#include <hack/actor_data.h>

class Actor
{
public:
    Actor(ActorID actor_id);
    ~Actor() {}

    const Stats&        stats() const { return _stats; }
    int                 dlevel() const { return _dlevel; }
    ActorID             actor_id() const { return _actor_id; }
    const ActorData&    actor_data() const { return ActorData::from_id(_actor_id); }
    Vector2i            pos() const { return _pos; }

    void    move(int x, int y);
    void    move_relative(int x, int y);
    void    move_dlevel(int dlevel);
    void    move_dlevel_relative(int d);

    bool    ct_check();

private:
    ActorID     _actor_id;
    Stats       _stats;
    Vector2i    _pos;
    int         _ct;
    int         _dlevel;
};

#endif
