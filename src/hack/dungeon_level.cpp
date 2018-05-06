#include <cmath>
#include <hack/dungeon_level.h>

DungeonLevel::DungeonLevel() : _tiles(nullptr)
{

}

DungeonLevel::DungeonLevel(Vector2i size) : _size(size)
{
    size_t count;

    count = size.x * size.y;
    _tiles = new TileID[size.x * size.y];
    _lit.resize(count);
    _image.resize(count);
}


DungeonLevel::DungeonLevel(DungeonLevel&& other) : _size(other._size), _tiles(other._tiles)
{
    other._size = Vector2i();
    other._tiles = nullptr;
    std::swap(_lit, other._lit);
    std::swap(_image, other._image);
}

DungeonLevel& DungeonLevel::operator=(DungeonLevel&& other)
{
    std::swap(_size, other._size);
    std::swap(_tiles, other._tiles);
    std::swap(_lit, other._lit);
    std::swap(_image, other._image);
    return *this;
}

DungeonLevel::~DungeonLevel()
{
    delete [] _tiles;
}

bool DungeonLevel::check_los(Vector2i a, Vector2i b) const
{
    return (check_los_directed(a, b) || check_los_directed(b, a));
}

Symbol DungeonLevel::remembered_sym(Vector2i pos) const
{
    int i;

    i = index(pos.x, pos.y);
    if (i == -1)
        return Symbol();
    return _image[i];
}

bool DungeonLevel::lit(Vector2i pos) const
{
    int i;

    i = index(pos.x, pos.y);
    if (i == -1)
        return false;
    return _lit[i];
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

Vector2i DungeonLevel::scan(TileID tile)
{
    Vector2i res;

    for (int i = 0; i < _size.x * _size.y; ++i)
    {
        if (_tiles[i] == tile)
        {
            res.x = i % _size.x;
            res.y = i / _size.x;
            return res;
        }
    }
    res.x = -1;
    res.y = -1;
    return res;
}

void DungeonLevel::resize(int x, int y)
{
    delete [] _tiles;
    _size.x = x;
    _size.y = y;
    _tiles = new TileID[x * y];
    _lit.clear();
    _lit.resize(x * y);
    _image.clear();
    _image.resize(x * y);
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

void DungeonLevel::light(Vector2i pos)
{
    int i;

    i = index(pos.x, pos.y);
    if (i != -1)
        _lit[i] = true;
}


void DungeonLevel::remember(Vector2i pos, Symbol sym)
{
    int i;

    i = index(pos.x, pos.y);
    if (i != -1)
        _image[i] = sym;
}

bool DungeonLevel::spawn_actor(ActorID actor, Vector2i position)
{
    if (TileData::from_id(at(position)).solid)
        return false;
    _actors.emplace_back(actor);
    _actors.back().move(position.x, position.y);
    return true;
}

bool DungeonLevel::spawn_random_actor(int difficulty)
{
    ActorID tmp;
    ActorID actor;
    Vector2i pos;

    actor = ActorID::None;
    for (size_t i = 0; i < 50; ++i)
    {
        tmp = ActorData::random_id();
        const ActorData& data = ActorData::from_id(tmp);
        if (data.difficulty <= difficulty && data.difficulty > 0)
        {
            actor = tmp;
            break;
        }
    }
    if (actor == ActorID::None)
        return false;
    for (size_t i = 0; i < 100; ++i)
    {
        pos.x = rand() % _size.x;
        pos.y = rand() % _size.y;
        if (spawn_actor(actor, pos))
            return true;
    }
    return false;
}

bool DungeonLevel::spawn_random_actor_tick(int difficulty)
{
    if (rand() % (20 * (_actors.size() + 1)))
        return false;
    return spawn_random_actor(difficulty);
}

int DungeonLevel::index(int x, int y) const
{
    if (x < 0 || x >= _size.x || y < 0 || y >= _size.y)
        return -1;
    return x + y * _size.x;
}

bool DungeonLevel::check_los_directed(Vector2i a, Vector2i b) const
{
    bool steep;
    int dx;
    int dy;
    int err;
    int ystep;
    int y;
    Vector2i tmp;

    steep = abs(b.y - a.y) > abs(b.x - a.x);
    if (steep)
    {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if (a.x > b.x)
    {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }
    dx = b.x - a.x;
    dy = round(abs(b.y - a.y));
    err = dx / 2;
    ystep = a.y < b.y ? 1 : -1;
    y = a.y;

    for (int x = a.x; x < b.x; ++x)
    {
        tmp.x = x;
        tmp.y = y;
        if (steep)
            std::swap(tmp.x, tmp.y);
        if (x == b.x && y == b.y)
            break;
        if (TileData::from_id(at(tmp)).solid)
            return false;
        err = err - dy;
        if (err < 0)
        {
            y += ystep;
            err += dx;
        }
    }
    return true;
}
