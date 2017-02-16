#ifndef GAME_H
#define GAME_H

#include <non_copyable.h>
#include <screen.h>
#include <dungeon_generator_standard.h>
#include <monster.h>
#include <renderer.h>

class Game : public NonCopyable
{
public:
    Game(Screen& screen);
    ~Game();

    void    loop();
    void    render();
    void    handleEvent();
    void    update();

    void    move_player(int x, int y);

private:
    Screen&         _screen;
    Renderer        _renderer;
    DungeonLevel    _dl;
    Monster         _player;
    bool            _over;
};

#endif
