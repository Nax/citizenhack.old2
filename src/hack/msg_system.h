#ifndef MSG_SYSTEM_H
#define MSG_SYSTEM_H

#include <string>
#include <hack/non_copyable.h>

class Game;
class Screen;
class MsgSystem : public NonCopyable
{
public:
    MsgSystem(Game& game, Screen& screen) : _game(game), _screen(screen) {}

    size_t          size_max();
    const char*     message() const { return _message.c_str(); }

    void    printf(const char* format, ...);
    void    puts(const char* str);
    void    clear();

private:
    void    more();

    Game&       _game;
    Screen&     _screen;
    std::string _message;
};

#endif
