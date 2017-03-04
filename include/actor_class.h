#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <wish.h>

enum class ActorClassID
{
    None,
    Humanoid,
    Reptile
};

struct ActorClass
{
public:
    wish_unicode    sym;

    static const ActorClass actor_classes[];

    static const ActorClass& from_id(ActorClassID actor_class_id)
    {
        return actor_classes[static_cast<int>(actor_class_id)];
    }
};

#endif
