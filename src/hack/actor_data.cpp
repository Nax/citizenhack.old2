#include <hack/actor_data.h>
#include <hack/archive_file.h>

ActorData* ActorData::actors_data = nullptr;

ActorID ActorData::random_id()
{
    return static_cast<ActorID>((rand() % (ActorCount - 1)) + 1);
}

void ActorData::load(const Archive& archive)
{
    ArchiveFile file;
    ActorData*  actors;
    uint64_t    count;

    file.open(archive, "actor");
    count = file.read64u();
    actors = new ActorData[count + 1];
    memset(actors, 0, sizeof(ActorData) * (count + 1));

    for (uint64_t i = 0; i < count; ++i)
    {
        ActorData* a = (actors + i + 1);

        a->actor_class_id = static_cast<ActorClassID>(file.read8u());
        a->difficulty = file.read8u();
        a->color = file.read8u();
    }

    ActorData::actors_data = actors;
}
