#include <cstdlib>
#include <hack/dungeon_generator_standard.h>

void DungeonGeneratorStandard::populate_rooms()
{
    size_t indices[2];

    indices[0] = rand() % _rooms.size();
    do
    {
        indices[1] = rand() % _rooms.size();
    } while (indices[0] == indices[1]);
    _level.set(room_rand_tile(_rooms[indices[0]]), TileID::StaircaseUp);
    _level.set(room_rand_tile(_rooms[indices[1]]), TileID::StaircaseDown);
}

Vector2i DungeonGeneratorStandard::room_rand_tile(Rect2i room)
{
    Vector2i pos;
    size_t off_x;
    size_t off_y;

    off_x = rand() % (room.size.x - 2) + 1;
    off_y = rand() % (room.size.y - 2) + 1;
    pos.x = room.origin.x + off_x;
    pos.y = room.origin.y + off_y;
    return pos;
}

Vector2i DungeonGeneratorStandard::room_door(Rect2i room)
{
    Vector2i pos;
    Vector2i tmp;

    pos = room_rand_wall(room);
    tmp = pos;
    if (pos.x == room.origin.x || pos.x == room.origin.x + room.size.x - 1)
    {
        tmp.y += 1;
        if (_level.at(tmp) == TileID::DoorClosed)
            return tmp;
        tmp.y -= 2;
        if (_level.at(tmp) == TileID::DoorClosed)
            return tmp;
    }
    else
    {
        tmp.x += 1;
        if (_level.at(tmp) == TileID::DoorClosed)
            return tmp;
        tmp.x -= 2;
        if (_level.at(tmp) == TileID::DoorClosed)
            return tmp;
    }
    return pos;
}

Vector2i DungeonGeneratorStandard::room_rand_wall(Rect2i room)
{
    Vector2i res;

    bool    horizontal;
    bool    direction;
    size_t  max;
    size_t  offset;

    horizontal = !!(rand() % 2);
    direction = !!(rand() % 2);
    max = horizontal ? room.size.x : room.size.y;
    offset = rand() % (max - 2) + 1;

    if (horizontal)
    {
        res.x = room.origin.x + offset;
        res.y = room.origin.y;
        if (direction)
            res.y += room.size.y - 1;
    }
    else
    {
        res.y = room.origin.y + offset;
        res.x = room.origin.x;
        if (direction)
            res.x += room.size.x - 1;
    }
    return res;
}

void DungeonGeneratorStandard::make_path(Vector2i src, Vector2i dst)
{
    Vector2i tmp;
    Vector2i dir;
    Vector2i diff;
    TileID tmp_tile;

    _level.set(src, TileID::DoorClosed);

    for (size_t a = 0; a < 500; ++a)
    {
        dir.x = 0;
        dir.y = 0;

        diff.x = dst.x - src.x;
        diff.y = dst.y - src.y;

        if (std::abs(diff.x) < std::abs(diff.y))
        {
            if (diff.y > 0)
                dir.y = 1;
            else
                dir.y = -1;
        }
        else
        {
            if (diff.x > 0)
                dir.x = 1;
            else
                dir.x = -1;
        }
        tmp.x = src.x + dir.x;
        tmp.y = src.y + dir.y;
        if (tmp.x == dst.x && tmp.y == dst.y)
        {
            _level.set(dst, TileID::DoorClosed);
            return;
        }
        tmp_tile = _level.at(tmp);
        if (tmp_tile != TileID::Corridor && tmp_tile != TileID::Rock)
        {
            bool done;
            Vector2i guess[2];

            done = false;
            guess[0] = src;
            guess[1] = src;
            if (dir.x)
            {
                guess[0].y += 1;
                guess[1].y -= 1;
            }
            else
            {
                guess[0].x += 1;
                guess[1].x -= 1;
            }
            if (rand() % 2)
                std::swap(guess[0], guess[1]);
            for (int i = 0; i < 2; ++i)
            {
                tmp_tile = _level.at(guess[i]);
                if (tmp_tile == TileID::Corridor || tmp_tile == TileID::Rock)
                {
                    tmp = guess[i];
                    done = true;
                    break;
                }
            }
            if (!done)
            {
                tmp = src;
                tmp.x -= dir.x;
                tmp.y -= dir.y;
            }
        }
        _level.set(tmp, TileID::Corridor);
        src = tmp;
    }
}

void DungeonGeneratorStandard::link_rooms(Rect2i room1, Rect2i room2)
{
    Vector2i src;
    Vector2i dst;

    src = room_door(room1);
    dst = room_door(room2);
    make_path(src, dst);
}

void DungeonGeneratorStandard::link_all_rooms()
{
    std::vector<std::vector<Rect2i>> room_tree;

    /* Seed the tree */
    for (auto room : _rooms)
    {
        std::vector<Rect2i> e;

        e.push_back(room);
        room_tree.push_back(e);
    }

    for (;;)
    {
        if (room_tree.size() == 1)
            break;

        size_t index1;
        size_t index2;

        index1 = rand() % room_tree.size();
        do
        {
            index2 = rand() % room_tree.size();
        } while (index1 == index2);

        std::vector<Rect2i>& set1 = room_tree[index1];
        std::vector<Rect2i>& set2 = room_tree[index2];

        Rect2i room1;
        Rect2i room2;

        room1 = set1[rand() % set1.size()];
        room2 = set2[rand() % set2.size()];

        link_rooms(room1, room2);

        for (auto r : set2)
            set1.push_back(r);
        room_tree.erase(room_tree.begin() + index2);
    }
}

void DungeonGeneratorStandard::make_rooms()
{
    Vector2i level_size;
    Rect2i room;

    _rooms.clear();
    level_size = _level.size();
    for (size_t attempts = 0; attempts < 120; ++attempts)
    {
        if (_rooms.size() >= 9)
            break;
        room.size.x     = (rand() % 5 + 2) + (rand() % 5 + 4);
        room.size.y     = (rand() % 4 + 2) + (rand() % 3 + 2);
        room.origin.x   = rand() % (level_size.x - room.size.x - 2) + 1;
        room.origin.y   = rand() % (level_size.y - room.size.y - 2) + 1;
        if (try_make_room(room))
            _rooms.push_back(room);
    }
}

bool DungeonGeneratorStandard::try_make_room(Rect2i room)
{
    for (int j = -1; j < room.size.y + 1; ++j)
    {
        for (int i = -1; i < room.size.x + 1; ++i)
        {
            if (_level.at(room.origin.x + i, room.origin.y + j) != TileID::Rock)
                return false;
        }
    }
    make_room(room);
    return true;
}

void DungeonGeneratorStandard::make_room(Rect2i room)
{
    Vector2i pos;

    for (int j = 0; j < room.size.y; ++j)
    {
        for (int i = 0; i < room.size.x; ++i)
        {
            pos.x = room.origin.x + i;
            pos.y = room.origin.y + j;

            if (i == 0 || i == (room.size.x - 1) || j == 0 || j == (room.size.y - 1))
                _level.set(pos, TileID::Wall);
            else
                _level.set(pos, TileID::Ground);
            _level.light(pos);
        }
    }
}

void DungeonGeneratorStandard::run()
{
    _level.resize(80, 21);
    _level.fill(TileID::Rock);
    make_rooms();
    link_all_rooms();
    populate_rooms();
}
