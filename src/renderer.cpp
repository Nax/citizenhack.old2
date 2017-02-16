#include <renderer.h>
#include <dungeon_level.h>

// Right = 1
// Left  = 2
// Up    = 4
// Down  = 8

static wish_unicode s_walls[] = {
    0x253c,
    0x2500,
    0x2500,
    0x2500,
    0x2502,
    0x2514,
    0x2518,
    0x2534,
    0x2502,
    0x250c,
    0x2510,
    0x252c,
    0x2502,
    0x251c,
    0x2524,
    0x253c
};

static wish_unicode wall_symbol(const DungeonLevel& dl, int x, int y)
{
    int score;

    score = 0;
    if (dl.at(x + 1, y) == TileID::Wall)
        score |= (1 << 0);
    if (dl.at(x - 1, y) == TileID::Wall)
        score |= (1 << 1);
    if (dl.at(x, y + 1) == TileID::Wall)
        score |= (1 << 3);
    if (dl.at(x, y - 1) == TileID::Wall)
        score |= (1 << 2);
    return s_walls[score];
}

void Renderer::render_level(const DungeonLevel& dl)
{
    wish_attr attr;
    wish_unicode cp;
    wish_view* view;
    Vector2i level_size = dl.size();

    wish_attr_init(&attr);
    view = _screen.main_view;
    for (int y = 0; y < level_size.y; ++y)
    {
        wish_move(view, 0, y);
        for (int x = 0; x < level_size.x; ++x)
        {
            TileID tile_id = dl.at(x, y);
            const TileData& tile_data = TileData::from_id(tile_id);
            if (tile_id == TileID::Wall)
                cp = wall_symbol(dl, x, y);
            else
                cp = tile_data.sym;
            wish_putchar(view, cp, attr);
        }
    }
}

void Renderer::render_monster(const Monster& mon)
{
    wish_attr attr;
    wish_view* view;
    wish_unicode cp;

    view = _screen.main_view;
    wish_attr_init(&attr);
    cp = mon.monster_data().sym;
    wish_mvputchar(view, mon.pos().x, mon.pos().y, cp, attr);
    wish_cursor_move(view, mon.pos().x, mon.pos().y);
}
