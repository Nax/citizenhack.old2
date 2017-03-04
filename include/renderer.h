#ifndef RENDERER_H
#define RENDERER_H

#include <non_copyable.h>
#include <screen.h>
#include <actor.h>

class DungeonLevel;
class Renderer : public NonCopyable
{
public:
    Renderer(Screen& screen) : _screen(screen) {}
    ~Renderer() {}

    void render_level(DungeonLevel& dl, const Actor& player);
    void render_actor(const DungeonLevel& dl, const Actor& player, const Actor& mon);
    void render_status(const Actor& player);
    void render_message(const char* str);

private:
    Screen&     _screen;
};

#endif
