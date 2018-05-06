#include <hack/game.h>

Game::Game(Screen& screen)
: _screen(screen)
, _msg_system(*this, screen)
, _renderer(screen)
, _player(ActorID::Human)
, _turn(0)
, _subturn(0)
{
    Vector2i start_pos;

    start_pos = _dungeon.level(0).scan(TileID::StaircaseUp);
    _player.move(start_pos.x, start_pos.y);
    _msg_system.puts("Welcome to CitizenHack!");
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
        update();
        render();
    }
}

void Game::render()
{
    DungeonLevel& dl = _dungeon.level(_player.dlevel());
    _screen.clear();
    _renderer.render_level(dl, _player);
    for (auto& m : dl.actors())
        _renderer.render_actor(dl, _player, m);
    _renderer.render_actor(dl, _player, _player);
    _renderer.render_status(*this, _player);
    _renderer.render_message(_msg_system.message());
    _screen.swap();
}

void Game::handleEvent()
{
    wish_unicode cp;

    cp = _screen.getchar();
    _msg_system.clear();
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
    _dungeon.level(_player.dlevel()).spawn_random_actor_tick(1);
    take_turns();
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

void Game::take_turns()
{
    for (;;)
    {
        _subturn++;
        if (_subturn == 10)
        {
            _subturn = 0;
            on_turn();
        }
        auto& actors = _dungeon.level(_player.dlevel()).actors();
        for (auto& a : actors)
        {
            if (a.ct_check())
            {
                // TODO: call AI
            }
        }
        if (_player.ct_check())
            return;
    }
}

void Game::on_turn()
{
    _turn++;
}
