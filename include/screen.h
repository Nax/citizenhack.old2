#ifndef SCREEN_H
#define SCREEN_H

#include <wish.h>
#include "non_copyable.h"

class Screen : public NonCopyable
{
public:
    Screen();
    ~Screen();

    void            handle_resize();
    void            swap();
    void            clear();
    wish_unicode    getchar();

    wish_term*  term;
    wish_view*  fullscreen;
    wish_view*  msg_bar;
    wish_view*  main_view;
    wish_view*  status_bar;
};

#endif
