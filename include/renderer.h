#ifndef RENDERER_H
#define RENDERER_H

#include <non_copyable.h>
#include <screen.h>
#include <monster.h>

class DungeonLevel;
class Renderer : public NonCopyable
{
public:
    Renderer(Screen& screen) : _screen(screen) {}
    ~Renderer() {}

    void render_level(const DungeonLevel& dl);
    void render_monster(const Monster& mon);

private:
    Screen&     _screen;
};

#endif
