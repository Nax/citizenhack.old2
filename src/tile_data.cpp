#include <tile_data.h>

const TileData TileData::tiles[] = {
    {"", ' ', 0, 0, 0, true},
    {"rock", ' ', 0, 0, 0, true},
    {"wall", 0, 15, 0, 0, true},
    {"ground", 0xb7, 15, 0, 0, false},
    {"corridor", '#', 7, 0, 0, false},
    {"open door", 0, 3, 0, 0, false},
    {"closed door", '+', 3, 0, 0, true},
    {"locked door", '+', 3, 0, 0, true}
};
