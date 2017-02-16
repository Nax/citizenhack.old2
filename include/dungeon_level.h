#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H

#include <non_copyable.h>
#include <vector.h>
#include <tile_data.h>

class DungeonLevel : public NonCopyable
{
public:
    DungeonLevel();
    DungeonLevel(Vector2i size);
    DungeonLevel(DungeonLevel&& other);
    DungeonLevel& operator=(DungeonLevel&& other);
    ~DungeonLevel();

    Vector2i    size() const { return _size; }
    TileID      at(int x, int y) const;
    TileID      at(Vector2i pos) const;

    void    resize(int x, int y);
    void    resize(Vector2i size);
    void    set(int x, int y, TileID tile);
    void    set(Vector2i pos, TileID tile);
    void    fill(TileID tile);

private:
    int     index(int x, int y) const;

    Vector2i    _size;
    TileID*     _tiles;
};

#endif
