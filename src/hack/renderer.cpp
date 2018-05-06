#include <hack/renderer.h>
#include <hack/dungeon_level.h>
#include <hack/game.h>

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

static bool check_visibility(const DungeonLevel& dl, const Actor& player, Vector2i target)
{
    Vector2i player_pos;

    player_pos = player.pos();
    if (target.x >= player_pos.x - 1 && target.x <= player_pos.x + 1 && target.y >= player_pos.y - 1 && target.y <= player_pos.y + 1)
        return true;
    else if (dl.lit(target) && dl.check_los(player_pos, target))
        return true;
    return false;
}

void Renderer::render_level(DungeonLevel& dl, const Actor& player)
{
    wish_attr attr;
    wish_unicode cp;
    wish_view* view;
    Vector2i level_size = dl.size();
    Vector2i tmp;
    Symbol sym;
    bool visible;
    Vector2i player_pos;

    player_pos = player.pos();
    view = _screen.main_view;
    for (int y = 0; y < level_size.y; ++y)
    {
        wish_move(view, 0, y);
        for (int x = 0; x < level_size.x; ++x)
        {
            visible = false;
            tmp.x = x;
            tmp.y = y;
            wish_attr_init(&attr);
            if (x >= player_pos.x - 1 && x <= player_pos.x + 1
                    && y >= player_pos.y - 1 && y <= player_pos.y + 1)
                visible = true;
            else if (dl.lit(tmp) && dl.check_los(player_pos, tmp))
                visible = true;
            if (!visible)
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
            if (tile_data.lit_color != -1)
                wish_color(&attr, tile_data.lit_color);
            else
                wish_color(&attr, tile_data.color);
            wish_putchar(view, cp, attr);
            sym = Symbol();
            sym.sym = cp;
            sym.color = tile_data.color;
            dl.remember(tmp, sym);
        }
    }
}

void Renderer::render_actor(const DungeonLevel& dl, const Actor& player, const Actor& mon)
{
    wish_attr attr;
    wish_view* view;
    wish_unicode cp;

    if (check_visibility(dl, player, mon.pos()))
    {
        view = _screen.main_view;
        wish_attr_init(&attr);
        cp = mon.actor_data().actor_class().sym;
        wish_color(&attr, mon.actor_data().color);
        wish_attr_set(&attr, mon.actor_data().flags);
        wish_mvputchar(view, mon.pos().x, mon.pos().y, cp, attr);
        wish_cursor_move(view, mon.pos().x, mon.pos().y);
    }
}

void Renderer::render_status(const Game& game, const Actor& player)
{
    wish_attr attr;
    wish_view* view;
    const Stats& stats = player.stats();
    int strength_major;
    int strength_minor;

    strength_major = stats.strength;
    if (strength_major > 118)
        strength_major -= 100;
    else if (strength_major >= 18)
    {
        strength_minor = strength_major - 18;
        strength_major = 18;
    }
    view = _screen.status_bar;
    wish_attr_init(&attr);
    wish_move(view, 10, 0);
    if (strength_major == 18)
    {
        if (strength_minor == 100)
            wish_puts(view, "St:18/**", attr);
        else
            wish_printf(view, "St:18/%02d", attr, strength_minor);
    }
    else
        wish_printf(view, "St:%-2d", attr, strength_major);
    wish_puts(view, " ", attr);
    wish_printf(view, "Dx:%-2d ", attr, stats.dexterity);
    wish_printf(view, "Co:%-2d ", attr, stats.constitution);
    wish_printf(view, "In:%-2d ", attr, stats.intelligence);
    wish_printf(view, "Wi:%-2d ", attr, stats.wisdom);
    wish_printf(view, "Ch:%-2d ", attr, stats.charisma);
    wish_mvprintf(view, 0, 1, "Dlvl:%-2d   ", attr, player.dlevel() + 1);
    wish_printf(view, "HP:%d(%d) ", attr, stats.hp, stats.hp);
    wish_printf(view, "MP:%d(%d) ", attr, stats.mp, stats.mp);
    wish_printf(view, "AC:%d ", attr, stats.ac);
    wish_printf(view, "Turn:%d", attr, game.turn());
}

void Renderer::render_message(const char* str)
{
    wish_attr attr;
    wish_view* view;

    view = _screen.msg_bar;
    wish_attr_init(&attr);
    wish_mvputs(view, 0, 0, str, attr);
}
