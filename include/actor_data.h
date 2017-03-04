#ifndef ACTOR_DATA_H
#define ACTOR_DATA_H

#include <wish.h>
#include <actor_class.h>
#include <actor_id.h>
#include <stats.h>

struct ActorData
{
    const char*     str;
    int             difficulty;
    ActorClassID  actor_class_id;
    int             color;
    int             flags;
    Stats           stats;

    const ActorClass& actor_class() const { return ActorClass::from_id(actor_class_id); }

    static const ActorData actors[];

    static const ActorData& from_id(ActorID actor)
    {
        return actors[static_cast<int>(actor)];
    }

    static ActorID random_id();
};

#endif
