#ifndef TILE_ID_H
#define TILE_ID_H

enum class TileID : unsigned char
{
    None,
    Rock,
    Wall,
    Ground,
    Corridor,
    DoorOpen,
    DoorClosed,
    DoorLocked,
    StaircaseUp,
    StaircaseDown
};

#endif
