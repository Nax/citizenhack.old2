#ifndef TILE_DATA_H
#define TILE_DATA_H

#include <wish.h>
#include <tile_id.h>

struct TileData
{
    const char*     name;
    wish_unicode    sym;
    int             color;
    int             bcolor;
    int             flags;
    int             lit_color;
    bool            solid:1;

    static const TileData& from_id(TileID id)
    {
        return tiles[static_cast<size_t>(id)];
    }

    static const TileData tiles[];
};

#endif
