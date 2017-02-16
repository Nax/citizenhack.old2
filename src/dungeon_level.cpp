#include <dungeon_level.h>

DungeonLevel::DungeonLevel() : _tiles(nullptr)
{

}

DungeonLevel::DungeonLevel(Vector2i size) : _size(size)
{
    _tiles = new TileID[size.x * size.y];
}


DungeonLevel::DungeonLevel(DungeonLevel&& other) : _size(other._size), _tiles(other._tiles)
{
    other._size = Vector2i();
    other._tiles = nullptr;
}

DungeonLevel& DungeonLevel::operator=(DungeonLevel&& other)
{
    std::swap(_size, other._size);
    std::swap(_tiles, other._tiles);
    return *this;
}

DungeonLevel::~DungeonLevel()
{
    delete [] _tiles;
}

TileID DungeonLevel::at(int x, int y) const
{
    int i;

    i = index(x, y);
    if (i == -1)
        return TileID::None;
    return _tiles[i];
}

TileID DungeonLevel::at(Vector2i pos) const
{
    return at(pos.x, pos.y);
}

void DungeonLevel::resize(int x, int y)
{
    delete [] _tiles;
    _size.x = x;
    _size.y = y;
    _tiles = new TileID[x * y];
}


void DungeonLevel::resize(Vector2i size)
{
    resize(size.x, size.y);
}

void DungeonLevel::set(int x, int y, TileID tile)
{
    int i;

    i = index(x, y);
    if (i >= 0)
        _tiles[i] = tile;
}

void DungeonLevel::set(Vector2i pos, TileID tile)
{
    set(pos.x, pos.y, tile);
}

void DungeonLevel::fill(TileID tile)
{
    size_t max;

    max = _size.x * _size.y;
    for (size_t i = 0; i < max; ++i)
        _tiles[i] = tile;
}

int DungeonLevel::index(int x, int y) const
{
    if (x < 0 || x >= _size.x || y < 0 || y >= _size.y)
        return -1;
    return x + y * _size.x;
}
