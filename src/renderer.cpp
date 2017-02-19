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

static bool tile_need_connect(TileID tile_id)
{
    switch (tile_id)
    {
        case TileID::Wall:
        case TileID::DoorClosed:
        case TileID::DoorLocked:
        case TileID::DoorOpen:
            return true;
        default:
            return false;
    }
}

static wish_unicode wall_symbol(const DungeonLevel& dl, int x, int y)
{
    int score;

    score = 0;
    if (tile_need_connect(dl.at(x + 1, y)))
        score |= (1 << 0);
    if (tile_need_connect(dl.at(x - 1, y)))
        score |= (1 << 1);
    if (tile_need_connect(dl.at(x, y + 1)))
        score |= (1 << 3);
    if (tile_need_connect(dl.at(x, y - 1)))
        score |= (1 << 2);
    return s_walls[score];
}

void Renderer::render_level(DungeonLevel& dl, const Monster& player)
{
    wish_attr attr;
    wish_unicode cp;
    wish_view* view;
    Vector2i level_size = dl.size();
    Vector2i tmp;
    Symbol sym;

    view = _screen.main_view;
    for (int y = 0; y < level_size.y; ++y)
    {
        wish_move(view, 0, y);
        for (int x = 0; x < level_size.x; ++x)
        {
            tmp.x = x;
            tmp.y = y;
            wish_attr_init(&attr);
            if (dl.check_los(player.pos(), tmp) == false)
            {
                sym = dl.remembered_sym(tmp);
                wish_color(&attr, sym.color);
                wish_putchar(view, sym.sym, attr);
                continue;
            }
            TileID tile_id = dl.at(x, y);
            const TileData& tile_data = TileData::from_id(tile_id);
            cp = tile_data.sym;
            if (cp == 0 && tile_need_connect(tile_id))
                cp = wall_symbol(dl, x, y);
            wish_color(&attr, tile_data.color);
            wish_putchar(view, cp, attr);
            sym = Symbol();
            sym.sym = cp;
            sym.color = tile_data.color;
            dl.remember(tmp, sym);
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

void Renderer::render_status(const Monster& player)
{
    wish_attr attr;
    wish_view* view;

    view = _screen.status_bar;
    wish_attr_init(&attr);
    wish_mvprintf(view, 0, 1, "Dlvl:%-2d", attr, player.dlevel() + 1);
}
