#ifndef ACTORS_H
#define ACTORS_H

#include <vector>
#include <non_copyable.h>
#include <types.h>
#include <vector.h>
#include <actor_id.h>

class Actors : public NonCopyable
{
public:
    Actors();
    ~Actors();

    ActorRef    create(ActorID actor_id, DungeonLevelRef dungeon_level, Vector2i position);
    void        destroy(ActorRef ref);

private:
    size_t                          _count;
    std::vector<ActorRef>           _free;
    std::vector<bool>               _used;
    std::vector<ActorID>            _id;
    std::vector<DungeonLevelRef>    _dungeon_levels;
    std::vector<Vector2i>           _positions;
};

#endif
