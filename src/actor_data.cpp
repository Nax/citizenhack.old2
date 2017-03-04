#include <actor_data.h>

const ActorData ActorData::actors[] = {
    {},
    {
        "human",
        0,
        ActorClassID::Humanoid,
        7,
        0,
        {10, 16, 8, 18, 14, 16, 16, 17, 12, 10}
    },
    {
        "newt",
        1,
        ActorClassID::Reptile,
        3,
        WISH_BOLD,
        {1, 6, 0, 3, 3, 3, 3, 3, 3, 3}
    }
};

ActorID ActorData::random_id()
{
    static constexpr const size_t max = sizeof(ActorData::actors) / sizeof(ActorData);

    return static_cast<ActorID>((rand() % (max - 1)) + 1);
}
