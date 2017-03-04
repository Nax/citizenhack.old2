#include <tile_data.h>

const TileData TileData::tiles[] = {
    {"", ' ', 0, 0, 0, -1, true},
    {"rock", ' ', 0, 0, 0, -1, true},
    {"wall", 0, 15, 0, 0, -1, true},
    {"ground", 0xb7, 8, 0, 0, 15, false},
    {"corridor", '#', 8, 0, 0, 7, false},
    {"open door", 0x25a0, 3, 0, 0, -1, false},
    {"closed door", '+', 3, 0, 0, -1, true},
    {"locked door", '+', 3, 0, 0, -1, true},
    {"up staircase", '<', 7, 0, 0, -1, false},
    {"down staircase", '>', 7, 0, 0, -1, false}
};
