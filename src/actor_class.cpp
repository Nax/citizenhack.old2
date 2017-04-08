#include <actor_class.h>
#include <archive_file.h>

ActorClass* ActorClass::actor_classes = nullptr;

void ActorClass::load(const Archive& archive)
{
    ArchiveFile file;
    ActorClass* classes;
    uint64_t count;

    file.open(archive, "actor_class");
    count = file.read64u();
    classes = new ActorClass[count + 1];
    memset(classes, 0, sizeof(ActorClass) * (count + 1));

    for (uint64_t i = 0; i < count; ++i)
    {
        uint32_t sym = file.read32u();
        classes[i + 1].sym = sym;
    }

    delete [] ActorClass::actor_classes;
    ActorClass::actor_classes = classes;
}
