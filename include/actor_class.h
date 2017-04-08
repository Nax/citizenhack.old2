#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include <wish.h>
#include <actor_class_id.h>
#include <archive.h>

struct ActorClass
{
public:
    wish_unicode    sym;

    static ActorClass* actor_classes;

    static const ActorClass& from_id(ActorClassID actor_class_id)
    {
        return actor_classes[static_cast<int>(actor_class_id)];
    }

    static void load(const Archive& archive);
};

#endif
