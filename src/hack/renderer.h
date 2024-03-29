#ifndef RENDERER_H
#define RENDERER_H

#include <hack/non_copyable.h>
#include <hack/screen.h>
#include <hack/actor.h>

class DungeonLevel;
class Game;
class Renderer : public NonCopyable
{
public:
    Renderer(Screen& screen) : _screen(screen) {}
    ~Renderer() {}

    void render_level(DungeonLevel& dl, const Actor& player);
    void render_actor(const DungeonLevel& dl, const Actor& player, const Actor& mon);
    void render_status(const Game& game, const Actor& player);
    void render_message(const char* str);

private:
    Screen&     _screen;
};

#endif
