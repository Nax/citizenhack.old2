#include <game.h>

Game::Game(Screen& screen) : _screen(screen), _renderer(screen), _player(MonsterID::Human)
{
    DungeonGeneratorStandard::generate(_dl);
    _player.move(12, 12);
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
    _renderer.render_level(_dl);
    _renderer.render_monster(_player);
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
    }
}

void Game::update()
{

}

void Game::move_player(int x, int y)
{
    Vector2i target;

    target = _player.pos();
    target.x += x;
    target.y += y;

    TileID tile_id = _dl.at(target);
    if (TileData::from_id(tile_id).solid == false)
        _player.move_relative(x, y);
    else if (tile_id == TileID::DoorClosed)
        _dl.set(target, TileID::DoorOpen);
}
