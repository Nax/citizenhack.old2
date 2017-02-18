#include <tile_data.h>

const TileData TileData::tiles[] = {
    {"", ' ', 0, 0, 0, true},
    {"rock", ' ', 0, 0, 0, true},
    {"wall", 0, 7, 0, 0, true},
    {"ground", 0xb7, 7, 0, 0, false},
    {"corridor", '#', 7, 0, 0, false},
    {"open door", '+', 3, 0, 0, false},
    {"closed door", 0, 3, 0, 0, true},
    {"locked door", 0, 3, 0, 0, true}
};
