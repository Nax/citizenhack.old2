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

    int     turn() const { return _turn; }

    void    loop();
    void    render();
    void    handleEvent();
    void    update();

    void    move_player(int x, int y);
    void    move_player_dlevel(int delta);

private:
    void    take_turns();
    void    on_turn();

    Screen&                 _screen;
    MsgSystem               _msg_system;
    Renderer                _renderer;
    Dungeon                 _dungeon;
    Actor                   _player;
    bool                    _over;
    int                     _turn;
    int                     _subturn;
};

#endif
