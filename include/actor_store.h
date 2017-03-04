#ifndef ACTOR_STORE_H
#define ACTOR_STORE_H

#include <vector>
#include <actor.h>

class ActorStore
{
public:
    ActorStore();
    ~ActorStore();

private:
    std::vector<Actor>    _actors;
    Actor                 _hero;
};

#endif
