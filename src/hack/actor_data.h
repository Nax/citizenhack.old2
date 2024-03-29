#ifndef ACTOR_DATA_H
#define ACTOR_DATA_H

#include <wish/wish.h>
#include <hack/actor_class.h>
#include <hack/actor_id.h>
#include <hack/stats.h>
#include <hack/archive.h>

struct ActorData
{
    ActorClassID    actor_class_id;
    int             difficulty;
    int             color;
    int             flags;

    const ActorClass& actor_class() const { return ActorClass::from_id(actor_class_id); }

    static ActorData* actors_data;

    static const ActorData& from_id(ActorID actor)
    {
        return actors_data[static_cast<int>(actor)];
    }

    static ActorID random_id();

    static void load(const Archive& archive);
};

#endif
