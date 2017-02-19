#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H

#include <vector>
#include <non_copyable.h>
#include <vector.h>
#include <tile_data.h>
#include <symbol.h>

class DungeonLevel : public NonCopyable
{
public:
    DungeonLevel();
    DungeonLevel(Vector2i size);
    DungeonLevel(DungeonLevel&& other);
    DungeonLevel& operator=(DungeonLevel&& other);
    ~DungeonLevel();

    Symbol      remembered_sym(Vector2i) const;
    bool        check_los(Vector2i a, Vector2i b) const;
    bool        lit(Vector2i pos) const;
    bool        empty() const { return _tiles == nullptr; }
    Vector2i    size() const { return _size; }
    TileID      at(int x, int y) const;
    TileID      at(Vector2i pos) const;
    Vector2i    scan(TileID tile);

    void    resize(int x, int y);
    void    resize(Vector2i size);
    void    set(int x, int y, TileID tile);
    void    set(Vector2i pos, TileID tile);
    void    fill(TileID tile);
    void    light(Vector2i pos);
    void    remember(Vector2i pos, Symbol sym);

private:
    int     index(int x, int y) const;
    bool    check_los_directed(Vector2i a, Vector2i b) const;

    Vector2i            _size;
    TileID*             _tiles;
    std::vector<Symbol> _image;
    std::vector<bool>   _lit;
};

#endif
