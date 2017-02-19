#include <game.h>

Game::Game(Screen& screen) : _screen(screen), _renderer(screen), _player(MonsterID::Human)
{
    Vector2i start_pos;

    start_pos = _dungeon.level(0).scan(TileID::StaircaseUp);
    _player.move(start_pos.x, start_pos.y);
}

Game::~Game()
{

}

void Game::loop()
{
    _over = false;
    render();
    while (!_over)
    {
        handleEvent();
        render();
        update();

    }
}

void Game::render()
{
    _screen.clear();
    _renderer.render_level(_dungeon.level(_player.dlevel()), _player);
    _renderer.render_monster(_player);
    _renderer.render_status(_player);
    _screen.swap();
}

void Game::handleEvent()
{
    wish_unicode cp;

    cp = _screen.getchar();
    switch (cp)
    {
        case 'q':
            _over = true;
            break;
        case 'h':
            move_player(-1, 0);
            break;
        case 'j':
            move_player(0, 1);
            break;
        case 'k':
            move_player(0, -1);
            break;
        case 'l':
            move_player(1, 0);
            break;
        case 'y':
            move_player(-1, -1);
            break;
        case 'u':
            move_player(1, -1);
            break;
        case 'b':
            move_player(-1, 1);
            break;
        case 'n':
            move_player(1, 1);
            break;
        case '>':
            move_player_dlevel(1);
            break;
        case '<':
            move_player_dlevel(-1);
            break;
    }
}

void Game::update()
{

}

void Game::move_player(int x, int y)
{
    DungeonLevel& level = _dungeon.level(_player.dlevel());
    Vector2i target;

    target = _player.pos();
    target.x += x;
    target.y += y;

    TileID tile_id = level.at(target);
    if (TileData::from_id(tile_id).solid == false)
        _player.move_relative(x, y);
    else if (tile_id == TileID::DoorClosed)
        level.set(target, TileID::DoorOpen);
}

void Game::move_player_dlevel(int delta)
{
    TileID src_tile;
    TileID dst_tile;
    Vector2i target;

    src_tile = TileID::StaircaseDown;
    dst_tile = TileID::StaircaseUp;
    if (delta < 0)
        std::swap(src_tile, dst_tile);
    if (_dungeon.level(_player.dlevel()).at(_player.pos()) != src_tile)
        return;
    _player.move_dlevel_relative(delta);
    target = _dungeon.level(_player.dlevel()).scan(dst_tile);
    _player.move(target.x, target.y);
}
