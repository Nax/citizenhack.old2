#ifndef GAME_H
#define GAME_H

#include <non_copyable.h>
#include <screen.h>
#include <dungeon.h>
#include <actor.h>
#include <renderer.h>
#include <msg_system.h>

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
    void    move_player_dlevel(int delta);

private:
    Screen&                 _screen;
    MsgSystem               _msg_system;
    Renderer                _renderer;
    Dungeon                 _dungeon;
    Actor                 _player;
    bool                    _over;
};

#endif
